#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int width; int height; int /*<<< orphan*/  blueBits; int /*<<< orphan*/  greenBits; int /*<<< orphan*/  redBits; int /*<<< orphan*/  refreshRate; } ;
struct TYPE_7__ {int number; int /*<<< orphan*/  window; int /*<<< orphan*/  closeable; } ;
typedef  TYPE_1__ Slot ;
typedef  TYPE_2__ GLFWvidmode ;
typedef  int /*<<< orphan*/  GLFWmonitor ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  GLFW_BLUE_BITS ; 
 int /*<<< orphan*/  GLFW_GREEN_BITS ; 
 int /*<<< orphan*/  GLFW_RED_BITS ; 
 int /*<<< orphan*/  GLFW_REFRESH_RATE ; 
 int /*<<< orphan*/  GL_TRUE ; 
 int /*<<< orphan*/  LC_ALL ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  char_callback ; 
 int /*<<< orphan*/  char_mods_callback ; 
 int /*<<< orphan*/  cursor_enter_callback ; 
 int /*<<< orphan*/  cursor_position_callback ; 
 int /*<<< orphan*/  drop_callback ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  framebuffer_size_callback ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  glfwCreateWindow (int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* glfwGetMonitorName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * glfwGetPrimaryMonitor () ; 
 TYPE_2__* glfwGetVideoMode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetCharCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetCharModsCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetCursorEnterCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetCursorPosCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetDropCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetErrorCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetFramebufferSizeCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetKeyCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetMonitorCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetMouseButtonCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetScrollCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowCloseCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowFocusCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowIconifyCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowPosCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowRefreshCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowSizeCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowUserPointer (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  glfwSwapInterval (int) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWaitEvents () ; 
 int /*<<< orphan*/  glfwWindowHint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ glfwWindowShouldClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_callback ; 
 int /*<<< orphan*/  monitor_callback ; 
 int /*<<< orphan*/  mouse_button_callback ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  scroll_callback ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  window_close_callback ; 
 int /*<<< orphan*/  window_focus_callback ; 
 int /*<<< orphan*/  window_iconify_callback ; 
 int /*<<< orphan*/  window_pos_callback ; 
 int /*<<< orphan*/  window_refresh_callback ; 
 int /*<<< orphan*/  window_size_callback ; 

int main(int argc, char** argv)
{
    Slot* slots;
    GLFWmonitor* monitor = NULL;
    int ch, i, width, height, count = 1;

    setlocale(LC_ALL, "");

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    printf("Library initialized\n");

    glfwSetMonitorCallback(monitor_callback);

    while ((ch = getopt(argc, argv, "hfn:")) != -1)
    {
        switch (ch)
        {
            case 'h':
                usage();
                exit(EXIT_SUCCESS);

            case 'f':
                monitor = glfwGetPrimaryMonitor();
                break;

            case 'n':
                count = (int) strtol(optarg, NULL, 10);
                break;

            default:
                usage();
                exit(EXIT_FAILURE);
        }
    }

    if (monitor)
    {
        const GLFWvidmode* mode = glfwGetVideoMode(monitor);

        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);

        width = mode->width;
        height = mode->height;
    }
    else
    {
        width  = 640;
        height = 480;
    }

    if (!count)
    {
        fprintf(stderr, "Invalid user\n");
        exit(EXIT_FAILURE);
    }

    slots = calloc(count, sizeof(Slot));

    for (i = 0;  i < count;  i++)
    {
        char title[128];

        slots[i].closeable = GL_TRUE;
        slots[i].number = i + 1;

        sprintf(title, "Event Linter (Window %i)", slots[i].number);

        if (monitor)
        {
            printf("Creating full screen window %i (%ix%i on %s)\n",
                   slots[i].number,
                   width, height,
                   glfwGetMonitorName(monitor));
        }
        else
        {
            printf("Creating windowed mode window %i (%ix%i)\n",
                   slots[i].number,
                   width, height);
        }

        slots[i].window = glfwCreateWindow(width, height, title, monitor, NULL);
        if (!slots[i].window)
        {
            free(slots);
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwSetWindowUserPointer(slots[i].window, slots + i);

        glfwSetWindowPosCallback(slots[i].window, window_pos_callback);
        glfwSetWindowSizeCallback(slots[i].window, window_size_callback);
        glfwSetFramebufferSizeCallback(slots[i].window, framebuffer_size_callback);
        glfwSetWindowCloseCallback(slots[i].window, window_close_callback);
        glfwSetWindowRefreshCallback(slots[i].window, window_refresh_callback);
        glfwSetWindowFocusCallback(slots[i].window, window_focus_callback);
        glfwSetWindowIconifyCallback(slots[i].window, window_iconify_callback);
        glfwSetMouseButtonCallback(slots[i].window, mouse_button_callback);
        glfwSetCursorPosCallback(slots[i].window, cursor_position_callback);
        glfwSetCursorEnterCallback(slots[i].window, cursor_enter_callback);
        glfwSetScrollCallback(slots[i].window, scroll_callback);
        glfwSetKeyCallback(slots[i].window, key_callback);
        glfwSetCharCallback(slots[i].window, char_callback);
        glfwSetCharModsCallback(slots[i].window, char_mods_callback);
        glfwSetDropCallback(slots[i].window, drop_callback);

        glfwMakeContextCurrent(slots[i].window);
        glfwSwapInterval(1);
    }

    printf("Main loop starting\n");

    for (;;)
    {
        for (i = 0;  i < count;  i++)
        {
            if (glfwWindowShouldClose(slots[i].window))
                break;
        }

        if (i < count)
            break;

        glfwWaitEvents();

        // Workaround for an issue with msvcrt and mintty
        fflush(stdout);
    }

    free(slots);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}