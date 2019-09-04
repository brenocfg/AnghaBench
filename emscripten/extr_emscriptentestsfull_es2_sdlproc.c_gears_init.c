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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  scalar_t__ GLfloat ;

/* Variables and functions */
 int /*<<< orphan*/  GL_CULL_FACE ; 
 int /*<<< orphan*/  GL_DEPTH_TEST ; 
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 scalar_t__* LightSourcePosition ; 
 void* LightSourcePosition_location ; 
 void* MaterialColor_location ; 
 void* ModelViewProjectionMatrix_location ; 
 void* NormalMatrix_location ; 
 int /*<<< orphan*/  assert (int) ; 
 void* create_gear (double,double,double,int,double) ; 
 char* fragment_shader ; 
 void* gear1 ; 
 void* gear2 ; 
 void* gear3 ; 
 int /*<<< orphan*/  glAttachShader (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindAttribLocation (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  glCompileShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCreateProgram () ; 
 int /*<<< orphan*/  glCreateShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetProgramInfoLog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  glGetShaderInfoLog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char*) ; 
 void* glGetUniformLocation (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glGetUniformfv (int /*<<< orphan*/ ,void*,scalar_t__*) ; 
 int /*<<< orphan*/  glLinkProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glShaderSource (int /*<<< orphan*/ ,int,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glUniform4fv (void*,int,scalar_t__*) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* vertex_shader ; 

__attribute__((used)) static void
gears_init(void)
{
   GLuint v, f, program;
   const char *p;
   char msg[512];

   glEnable(GL_CULL_FACE);
   glEnable(GL_DEPTH_TEST);

   /* Compile the vertex shader */
   p = vertex_shader;
   v = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(v, 1, &p, NULL);
   glCompileShader(v);
   glGetShaderInfoLog(v, sizeof msg, NULL, msg);
   printf("vertex shader info: %s\n", msg);

   /* Compile the fragment shader */
   p = fragment_shader;
   f = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(f, 1, &p, NULL);
   glCompileShader(f);
   glGetShaderInfoLog(f, sizeof msg, NULL, msg);
   printf("fragment shader info: %s\n", msg);

   /* Create and link the shader program */
   program = glCreateProgram();
   glAttachShader(program, v);
   glAttachShader(program, f);
   glBindAttribLocation(program, 0, "position");
   glBindAttribLocation(program, 1, "normal");

   glLinkProgram(program);
   glGetProgramInfoLog(program, sizeof msg, NULL, msg);
   printf("info: %s\n", msg);

   /* Enable the shaders */
   glUseProgram(program);

   /* Get the locations of the uniforms so we can access them */
   ModelViewProjectionMatrix_location = glGetUniformLocation(program, "ModelViewProjectionMatrix");
   NormalMatrix_location = glGetUniformLocation(program, "NormalMatrix");
   LightSourcePosition_location = glGetUniformLocation(program, "LightSourcePosition");
   MaterialColor_location = glGetUniformLocation(program, "MaterialColor");

   /* Set the LightSourcePosition uniform which is constant throught the program */
   glUniform4fv(LightSourcePosition_location, 1, LightSourcePosition);

   {
      GLfloat LightSourcePosition_copy[4];
      glGetUniformfv(program, LightSourcePosition_location, LightSourcePosition_copy);
      for (uint32_t i = 0; i < 4; ++i) {
        assert(LightSourcePosition[i] == LightSourcePosition_copy[i]);
      }
   }

   /* make the gears */
   gear1 = create_gear(1.0, 4.0, 1.0, 20, 0.7);
   gear2 = create_gear(0.5, 2.0, 2.0, 10, 0.7);
   gear3 = create_gear(1.3, 2.0, 0.5, 10, 0.7);
}