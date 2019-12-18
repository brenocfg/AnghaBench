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
typedef  int /*<<< orphan*/  log_info ;
typedef  int /*<<< orphan*/  fft_t ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLsizei ;
typedef  scalar_t__ GLint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_LINK_STATUS ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 int /*<<< orphan*/  RETRO_LOG_ERROR ; 
 int /*<<< orphan*/  fft_compile_shader (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  glAttachShader (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCreateProgram () ; 
 int /*<<< orphan*/  glDeleteShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetProgramInfoLog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  glGetProgramiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  glLinkProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_cb (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static GLuint fft_compile_program(fft_t *fft,
      const char *vertex_source, const char *fragment_source)
{
   GLint status = 0;
   GLuint prog  = glCreateProgram();
   GLuint vert  = fft_compile_shader(fft, GL_VERTEX_SHADER, vertex_source);
   GLuint frag  = fft_compile_shader(fft, GL_FRAGMENT_SHADER, fragment_source);

   glAttachShader(prog, vert);
   glAttachShader(prog, frag);
   glLinkProgram(prog);

   glGetProgramiv(prog, GL_LINK_STATUS, &status);

   if (!status)
   {
      char log_info[8 * 1024];
      GLsizei log_len;

      log_cb(RETRO_LOG_ERROR, "Failed to link.\n");
      glGetProgramInfoLog(prog, sizeof(log_info), &log_len, log_info);
      log_cb(RETRO_LOG_ERROR, "ERROR: %s\n", log_info);
   }

   glDeleteShader(vert);
   glDeleteShader(frag);
   return prog;
}