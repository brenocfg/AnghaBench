#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  GLvoid ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  scalar_t__ GLint ;
typedef  float GLfloat ;
typedef  scalar_t__ GLenum ;
typedef  char GLchar ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ GLEW_OK ; 
 int GLUT_DEPTH ; 
 int GLUT_DOUBLE ; 
 int GLUT_RGBA ; 
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_COMPILE_STATUS ; 
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 scalar_t__ GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_INFO_LOG_LENGTH ; 
 int /*<<< orphan*/  GL_LINK_STATUS ; 
 int /*<<< orphan*/  GL_STATIC_DRAW ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 int /*<<< orphan*/  REPORT_RESULT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fullscreen ; 
 int /*<<< orphan*/  glAttachShader (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindAttribLocation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindVertexArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int,float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCompileShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCreateProgram () ; 
 int /*<<< orphan*/  glCreateShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGenVertexArrays (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glGetProgramInfoLog (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  glGetProgramiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  glGetShaderInfoLog (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  glGetShaderiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  glLinkProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glShaderSource (int /*<<< orphan*/ ,int,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 char* glewGetErrorString (scalar_t__) ; 
 scalar_t__ glewInit () ; 
 int glutCreateWindow (char*) ; 
 int /*<<< orphan*/  glutDestroyWindow (int) ; 
 int /*<<< orphan*/  glutDisplayFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutIdleFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutInit (int*,char**) ; 
 int /*<<< orphan*/  glutInitDisplayMode (int) ; 
 int /*<<< orphan*/  glutInitWindowSize (int,int) ; 
 int /*<<< orphan*/  glutKeyboardFunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glutMainLoop () ; 
 int /*<<< orphan*/  glutReshapeFunc (int /*<<< orphan*/ ) ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  onDisplay ; 
 int /*<<< orphan*/  onIdle ; 
 int /*<<< orphan*/  onKeyboard ; 
 int /*<<< orphan*/  onReshape ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main(int argc, char* argv[])
{
  int win;
  GLuint vertex_shader;
  GLuint fragment_shader;
  GLuint program;
  GLuint vbo;
  GLuint vao;
  GLfloat vertices[] = {
    /*
       x,    y,
    */

    -1.f, -1.f,
     1.f, -1.f,
    -1.f,  1.f,

     1.f, -1.f,
     1.f,  1.f,
    -1.f,  1.f,
  };

  glutInit(&argc, argv);
  glutInitWindowSize(600, 450);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  win = glutCreateWindow(__FILE__);

#ifndef __EMSCRIPTEN__
  GLenum err = glewInit();
  if (err != GLEW_OK) {
    printf("error: %s\n", glewGetErrorString(err));
    glutDestroyWindow(win);
    REPORT_RESULT(0);
    return EXIT_FAILURE;
  }
#endif

  glEnable(GL_DEPTH_TEST);
  {
    const GLchar* str = "precision mediump float;\n"
                        "attribute vec2 aPosition;\n"
                        "varying vec2 vPosition;\n"
                        "void main()\n"
                        "{\n"
                        "  gl_Position = vec4(aPosition, 0.0, 1.0);\n"
                        "  vPosition = aPosition;\n"
                        "}\n";
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &str, NULL);
    glCompileShader(vertex_shader);
    {
      GLint params;
      GLchar* log;
      glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &params);
      if (params == GL_FALSE) {
        glGetShaderiv(vertex_shader, GL_INFO_LOG_LENGTH, &params);
        log = malloc(params);
        glGetShaderInfoLog(vertex_shader, params, NULL, log);
        printf("%s", log);
        free(log);
        glutDestroyWindow(win);
        REPORT_RESULT(0);
        return EXIT_FAILURE;
      }
    }
  }
  {
    const GLchar* str = "precision mediump float;\n"
                        "varying vec2 vPosition;\n"
                        "void main()\n"
                        "{\n"
                        "  if (abs(vPosition.x) > 0.9 || abs(vPosition.y) > 0.9) {\n"
                        "    gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
                        "  } else {\n"
                        "    gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
                        "  }\n"
                        "}\n";
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &str, NULL);
    glCompileShader(fragment_shader);
    {
      GLint params;
      GLchar* log;
      glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &params);
      if (params == GL_FALSE) {
        glGetShaderiv(fragment_shader, GL_INFO_LOG_LENGTH, &params);
        log = malloc(params);
        glGetShaderInfoLog(fragment_shader, params, NULL, log);
        printf("%s", log);
        free(log);
        glutDestroyWindow(win);
        REPORT_RESULT(0);
        return EXIT_FAILURE;
      }
    }
  }
  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glBindAttribLocation(program, 0, "aPosition");
  glLinkProgram(program);
  {
    GLint params;
    GLchar* log;
    glGetProgramiv(program, GL_LINK_STATUS, &params);
    if (params == GL_FALSE) {
      glGetProgramiv(program, GL_INFO_LOG_LENGTH, &params);
      log = malloc(params);
      glGetProgramInfoLog(program, params, NULL, log);
      printf("%s", log);
      free(log);
      glutDestroyWindow(win);
      REPORT_RESULT(0);
      return EXIT_FAILURE;
    }
  }
  glUseProgram(program);
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0);
  glEnableVertexAttribArray(0);

#ifndef __EMSCRIPTEN__
  fullscreen = 0;
#endif

  printf("You should see a green rectangle with red borders.\n");
  printf("Press 'f' or click the 'Fullscreen' button on the upper right corner to enter full screen, and press 'f' or ESC to exit.\n");
  printf("No matter 'Resize canvas' is checked or not, you should see the whole screen filled by the rectangle when in full screen, and after exiting, the rectangle should be restored in the window.\n");

  glutDisplayFunc(onDisplay);
  glutReshapeFunc(onReshape);
  glutKeyboardFunc(onKeyboard);
  glutIdleFunc(onIdle);
  glutMainLoop();

  glutDestroyWindow(win);
  return EXIT_SUCCESS;
}