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
typedef  scalar_t__ (* PFNGLGETSTRINGIPROC ) (int /*<<< orphan*/ ,int) ;
typedef  char GLubyte ;
typedef  int GLint ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int GLFW_OPENGL_API ; 
 int /*<<< orphan*/  GL_EXTENSIONS ; 
 int /*<<< orphan*/  GL_NUM_EXTENSIONS ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char* get_api_name (int) ; 
 int /*<<< orphan*/  glGetIntegerv (int /*<<< orphan*/ ,int*) ; 
 char* glGetString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwGetProcAddress (char*) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  putchar (char const) ; 
 int /*<<< orphan*/  puts (char const*) ; 

__attribute__((used)) static void list_extensions(int api, int major, int minor)
{
    int i;
    GLint count;
    const GLubyte* extensions;

    printf("%s context supported extensions:\n", get_api_name(api));

    if (api == GLFW_OPENGL_API && major > 2)
    {
        PFNGLGETSTRINGIPROC glGetStringi =
            (PFNGLGETSTRINGIPROC) glfwGetProcAddress("glGetStringi");
        if (!glGetStringi)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glGetIntegerv(GL_NUM_EXTENSIONS, &count);

        for (i = 0;  i < count;  i++)
            puts((const char*) glGetStringi(GL_EXTENSIONS, i));
    }
    else
    {
        extensions = glGetString(GL_EXTENSIONS);
        while (*extensions != '\0')
        {
            if (*extensions == ' ')
                putchar('\n');
            else
                putchar(*extensions);

            extensions++;
        }
    }

    putchar('\n');
}