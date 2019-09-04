#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  verts ;
struct TYPE_4__ {int enableExtensionsByDefault; int majorVersion; scalar_t__ minorVersion; scalar_t__ premultipliedAlpha; scalar_t__ failIfMajorPerformanceCaveat; scalar_t__ preserveDrawingBuffer; scalar_t__ antialias; scalar_t__ stencil; scalar_t__ depth; scalar_t__ alpha; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  TYPE_1__ EmscriptenWebGLContextAttributes ;
typedef  int /*<<< orphan*/  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ;
typedef  int /*<<< orphan*/  EMSCRIPTEN_RESULT ;

/* Variables and functions */
 char* EMSCRIPTEN_EVENT_TARGET_DOCUMENT ; 
 char* EMSCRIPTEN_EVENT_TARGET_WINDOW ; 
 int /*<<< orphan*/  GL_ARRAY_BUFFER ; 
 int /*<<< orphan*/  GL_FLOAT ; 
 int /*<<< orphan*/  GL_FRAGMENT_SHADER ; 
 int /*<<< orphan*/  GL_STATIC_DRAW ; 
 int /*<<< orphan*/  GL_VERTEX_SHADER ; 
 int /*<<< orphan*/  TEST_RESULT (int /*<<< orphan*/  (*) (char*,void*,int,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  draw ; 
 int /*<<< orphan*/  emscripten_set_click_callback (char*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_set_dblclick_callback (char*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_set_fullscreenchange_callback (char*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_set_keypress_callback (char*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_set_main_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_set_mousedown_callback (char*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_set_mouseup_callback (char*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emscripten_webgl_create_context (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  emscripten_webgl_init_context_attributes (TYPE_1__*) ; 
 int /*<<< orphan*/  emscripten_webgl_make_context_current (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fullscreenchange_callback ; 
 int /*<<< orphan*/  glAttachShader (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBindAttribLocation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glBindBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glBufferData (int /*<<< orphan*/ ,int,float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCompileShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glCreateProgram () ; 
 int /*<<< orphan*/  glCreateShader (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnableVertexAttribArray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenBuffers (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glLinkProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glShaderSource (int /*<<< orphan*/ ,int,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glVertexAttribPointer (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_callback ; 
 int /*<<< orphan*/  mouse_callback ; 
 int /*<<< orphan*/  on_button_click ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  program ; 

int main()
{
  EmscriptenWebGLContextAttributes attr;
  emscripten_webgl_init_context_attributes(&attr);
  attr.alpha = attr.depth = attr.stencil = attr.antialias = attr.preserveDrawingBuffer = attr.failIfMajorPerformanceCaveat = 0;
  attr.enableExtensionsByDefault = 1;
  attr.premultipliedAlpha = 0;
  attr.majorVersion = 1;
  attr.minorVersion = 0;
  EMSCRIPTEN_WEBGL_CONTEXT_HANDLE ctx = emscripten_webgl_create_context("#canvas", &attr);
  emscripten_webgl_make_context_current(ctx);
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  const char *vss = "attribute vec4 vPosition; uniform mat4 mat; void main() { gl_Position = mat * vPosition; }";
  glShaderSource(vs, 1, &vss, 0);
  glCompileShader(vs);
  GLuint ps = glCreateShader(GL_FRAGMENT_SHADER);
  const char *pss = "precision lowp float; uniform vec3 colors[3]; void main() { gl_FragColor = vec4(1,0,0,1); }";
  glShaderSource(ps, 1, &pss, 0);
  glCompileShader(ps);
  program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, ps);
  glBindAttribLocation(program, 0, "vPosition");
  glLinkProgram(program);
  glUseProgram(program);

  GLuint vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  float verts[] = { 0.0, 0.5, 0.0, -0.5, -0.5, 0.0, 0.5, -0.5, 0.0 };
  glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
  glEnableVertexAttribArray(0);

  EMSCRIPTEN_RESULT ret = emscripten_set_keypress_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, 1, key_callback);
  TEST_RESULT(emscripten_set_keypress_callback);

  ret = emscripten_set_fullscreenchange_callback(EMSCRIPTEN_EVENT_TARGET_DOCUMENT, 0, 1, fullscreenchange_callback);
  TEST_RESULT(emscripten_set_fullscreenchange_callback);

  // For Internet Explorer, fullscreen and pointer lock requests cannot be run
  // from inside keyboard event handlers. Therefore we must register a callback to
  // mouse events (any other than mousedown) to activate deferred fullscreen/pointerlock
  // requests to occur for IE. The callback itself can be a no-op.
  ret = emscripten_set_click_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, 1, mouse_callback);
  TEST_RESULT(emscripten_set_click_callback);
  ret = emscripten_set_mousedown_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, 1, mouse_callback);
  TEST_RESULT(emscripten_set_mousedown_callback);
  ret = emscripten_set_mouseup_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, 1, mouse_callback);
  TEST_RESULT(emscripten_set_mouseup_callback);
  ret = emscripten_set_dblclick_callback(EMSCRIPTEN_EVENT_TARGET_WINDOW, 0, 1, mouse_callback);
  TEST_RESULT(emscripten_set_dblclick_callback);

  emscripten_set_click_callback("#b0", (void*)0, 1, on_button_click);
  emscripten_set_click_callback("#b1", (void*)1, 1, on_button_click);
  emscripten_set_click_callback("#b2", (void*)2, 1, on_button_click);
  emscripten_set_click_callback("#b3", (void*)3, 1, on_button_click);
  emscripten_set_click_callback("#b4", (void*)4, 1, on_button_click);
  emscripten_set_click_callback("#b5", (void*)5, 1, on_button_click);
  emscripten_set_click_callback("#b6", (void*)6, 1, on_button_click);
  emscripten_set_click_callback("#b7", (void*)7, 1, on_button_click);
  emscripten_set_click_callback("#b8", (void*)8, 1, on_button_click);
  emscripten_set_click_callback("#b9", (void*)9, 1, on_button_click);
  emscripten_set_click_callback("#b10", (void*)10, 1, on_button_click);
  emscripten_set_click_callback("#b11", (void*)11, 1, on_button_click);
  emscripten_set_click_callback("#b12", (void*)12, 1, on_button_click);
  emscripten_set_click_callback("#b13", (void*)13, 1, on_button_click);
  emscripten_set_click_callback("#b14", (void*)14, 1, on_button_click);
  emscripten_set_click_callback("#b15", (void*)15, 1, on_button_click);
  emscripten_set_click_callback("#b16", (void*)16, 1, on_button_click);

  printf("To finish this test, press f to enter fullscreen mode, and then exit it.\n");
  printf("On IE, press a mouse key over the canvas after pressing f to activate the fullscreen request event.\n");

  emscripten_set_main_loop(draw, 0, 0);
  return 0;
}