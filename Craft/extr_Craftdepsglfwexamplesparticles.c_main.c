#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  thrd_t ;
struct TYPE_5__ {double t; float dt; int /*<<< orphan*/  d_done; int /*<<< orphan*/  p_done; int /*<<< orphan*/  particles_lock; scalar_t__ d_frame; scalar_t__ p_frame; } ;
struct TYPE_4__ {int width; int height; int /*<<< orphan*/  refreshRate; int /*<<< orphan*/  blueBits; int /*<<< orphan*/  greenBits; int /*<<< orphan*/  redBits; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  TYPE_1__ GLFWvidmode ;
typedef  int /*<<< orphan*/  GLFWmonitor ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  F_TEX_HEIGHT ; 
 int /*<<< orphan*/  F_TEX_WIDTH ; 
 int /*<<< orphan*/  GLFW_BLUE_BITS ; 
 int /*<<< orphan*/  GLFW_CURSOR ; 
 int /*<<< orphan*/  GLFW_CURSOR_DISABLED ; 
 int /*<<< orphan*/  GLFW_GREEN_BITS ; 
 int /*<<< orphan*/  GLFW_RED_BITS ; 
 int /*<<< orphan*/  GLFW_REFRESH_RATE ; 
 int /*<<< orphan*/  GL_CLAMP ; 
 int /*<<< orphan*/  GL_FILL ; 
 int /*<<< orphan*/  GL_FRONT_AND_BACK ; 
 int /*<<< orphan*/  GL_LIGHT_MODEL_COLOR_CONTROL_EXT ; 
 int /*<<< orphan*/  GL_LINEAR ; 
 int /*<<< orphan*/  GL_LUMINANCE ; 
 int /*<<< orphan*/  GL_REPEAT ; 
 int /*<<< orphan*/  GL_SEPARATE_SPECULAR_COLOR_EXT ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_S ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_T ; 
 int /*<<< orphan*/  GL_UNPACK_ALIGNMENT ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 int /*<<< orphan*/  P_TEX_HEIGHT ; 
 int /*<<< orphan*/  P_TEX_WIDTH ; 
 int /*<<< orphan*/  cnd_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  draw_scene (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  floor_tex_id ; 
 int /*<<< orphan*/  floor_texture ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  glBindTexture (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGenTextures (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glLightModeli (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glPixelStorei (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glPolygonMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glTexImage2D (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glTexParameteri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * glfwCreateWindow (int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwDestroyWindow (int /*<<< orphan*/ *) ; 
 scalar_t__ glfwExtensionSupported (char*) ; 
 int /*<<< orphan*/  glfwGetFramebufferSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/ * glfwGetPrimaryMonitor () ; 
 int /*<<< orphan*/  glfwGetTime () ; 
 TYPE_1__* glfwGetVideoMode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwPollEvents () ; 
 int /*<<< orphan*/  glfwSetFramebufferSizeCallback (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int,int)) ; 
 int /*<<< orphan*/  glfwSetInputMode (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetKeyCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetTime (double) ; 
 int /*<<< orphan*/  glfwSwapBuffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSwapInterval (int) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWindowHint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwWindowShouldClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_callback ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_timed ; 
 int /*<<< orphan*/  particle_tex_id ; 
 int /*<<< orphan*/  particle_texture ; 
 int /*<<< orphan*/  physics_thread_main ; 
 int /*<<< orphan*/  resize_callback (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ thrd_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thrd_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ thrd_success ; 
 TYPE_2__ thread_sync ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ wireframe ; 

int main(int argc, char** argv)
{
    int ch, width, height;
    thrd_t physics_thread = 0;
    GLFWwindow* window;
    GLFWmonitor* monitor = NULL;

    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    while ((ch = getopt(argc, argv, "fh")) != -1)
    {
        switch (ch)
        {
            case 'f':
                monitor = glfwGetPrimaryMonitor();
                break;
            case 'h':
                usage();
                exit(EXIT_SUCCESS);
        }
    }

    if (monitor)
    {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

        width  = mode->width;
        height = mode->height;
    }
    else
    {
        width  = 640;
        height = 480;
    }

    window = glfwCreateWindow(width, height, "Particle Engine", monitor, NULL);
    if (!window)
    {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    if (monitor)
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(window, resize_callback);
    glfwSetKeyCallback(window, key_callback);

    // Set initial aspect ratio
    glfwGetFramebufferSize(window, &width, &height);
    resize_callback(window, width, height);

    // Upload particle texture
    glGenTextures(1, &particle_tex_id);
    glBindTexture(GL_TEXTURE_2D, particle_tex_id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, P_TEX_WIDTH, P_TEX_HEIGHT,
                 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, particle_texture);

    // Upload floor texture
    glGenTextures(1, &floor_tex_id);
    glBindTexture(GL_TEXTURE_2D, floor_tex_id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, F_TEX_WIDTH, F_TEX_HEIGHT,
                 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, floor_texture);

    if (glfwExtensionSupported("GL_EXT_separate_specular_color"))
    {
        glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL_EXT,
                      GL_SEPARATE_SPECULAR_COLOR_EXT);
    }

    // Set filled polygon mode as default (not wireframe)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    wireframe = 0;

    // Set initial times
    thread_sync.t  = 0.0;
    thread_sync.dt = 0.001f;
    thread_sync.p_frame = 0;
    thread_sync.d_frame = 0;

    mtx_init(&thread_sync.particles_lock, mtx_timed);
    cnd_init(&thread_sync.p_done);
    cnd_init(&thread_sync.d_done);

    if (thrd_create(&physics_thread, physics_thread_main, window) != thrd_success)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetTime(0.0);

    while (!glfwWindowShouldClose(window))
    {
        draw_scene(window, glfwGetTime());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    thrd_join(physics_thread, NULL);

    glfwDestroyWindow(window);
    glfwTerminate();

    exit(EXIT_SUCCESS);
}