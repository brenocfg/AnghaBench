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
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLint ;
typedef  char GLchar ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  GLFW_CLIENT_API ; 
 int /*<<< orphan*/  GLFW_CONTEXT_VERSION_MAJOR ; 
 int /*<<< orphan*/  GLFW_CONTEXT_VERSION_MINOR ; 
 int GLFW_OPENGL_ES_API ; 
 int /*<<< orphan*/  GL_FALSE ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_UNSIGNED_INT ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 int /*<<< orphan*/  glAttachShader (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCompileShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCreateProgram () ; 
 int /*<<< orphan*/  glCreateShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetAttribLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glLinkProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glShaderSource (int /*<<< orphan*/ ,int,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribIPointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int const*) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float const*) ; 
 int /*<<< orphan*/ * glfwCreateWindow (int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetFramebufferSizeCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowCloseCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWindowHint (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  onClose ; 
 int /*<<< orphan*/  onDraw (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  onResize ; 

int main()
{
  GLFWwindow* window;

  if (!glfwInit()) {
    return EXIT_FAILURE;
  }
  glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  window = glfwCreateWindow(640, 480, "Client-side Vertex Arrays", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return EXIT_FAILURE;
  }
  glfwSetFramebufferSizeCallback(window, onResize);
  glfwSetWindowCloseCallback(window, onClose);
  glfwMakeContextCurrent(window);

  GLuint vertex_shader;
  GLuint fragment_shader;
  GLuint program;
  {
    const GLchar* source = "#version 300 es                            \n"
                           "                                           \n"
                           "in vec2 aPosition;                         \n"
                           "in uvec3 aColor;                           \n"
                           "out vec4 color;                            \n"
                           "                                           \n"
                           "void main()                                \n"
                           "{                                          \n"
                           "  gl_Position = vec4(aPosition, 0.f, 1.f); \n"
                           "  color = vec4(vec3(aColor) / 255.f, 1.f); \n"
                           "}                                          \n";
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &source, NULL);
    glCompileShader(vertex_shader);
  }
  {
    const GLchar* source = "#version 300 es          \n"
                           "                         \n"
                           "precision mediump float; \n"
                           "                         \n"
                           "in vec4 color;           \n"
                           "out vec4 FragColor;      \n"
                           "                         \n"
                           "void main()              \n"
                           "{                        \n"
                           "  FragColor = color;     \n"
                           "}                        \n";
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &source, NULL);
    glCompileShader(fragment_shader);
  }
  program = glCreateProgram();
  glAttachShader(program, vertex_shader);
  glAttachShader(program, fragment_shader);
  glLinkProgram(program);
  glUseProgram(program);
  {
    static const float position[] = {
      -1.f, -1.f,
       1.f, -1.f,
       0.f,  1.f,
    };
    GLint location;
    location = glGetAttribLocation(program, "aPosition");
    glVertexAttribPointer(location, 2, GL_FLOAT, GL_FALSE, 0, position);
    glEnableVertexAttribArray(location);
  }
  {
    static const unsigned int color[] = {
      255,   0,   0,
        0, 255,   0,
        0,   0, 255,
    };
    GLint location;
    location = glGetAttribLocation(program, "aColor");
    glVertexAttribIPointer(location, 3, GL_UNSIGNED_INT, 0, color);
    glEnableVertexAttribArray(location);
  }

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop_arg(onDraw, &window, 0, 1);
#else
  while (1) {
    onDraw(&window);
  }
#endif

  return EXIT_FAILURE; // not reached
}