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
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fgetc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 scalar_t__ strstr (char const*,char*) ; 

void on_file_drop(GLFWwindow *window, int count, const char **paths) {
  for (int i = 0; i < count; ++i) {
    printf("dropped file %s\n", paths[i]);

    FILE *fp = fopen(paths[i], "rb");
    if (!fp) {
        printf("failed to open %s\n", paths[i]);
        perror("fopen");
#ifdef REPORT_RESULT
        REPORT_RESULT(0);
#endif
        return;
    }
    int c;
    long size = 0;
    bool dump = strstr(paths[i], ".txt") != 0;
    if (dump) printf("text file contents (first 100 bytes): ");
    while ((c = fgetc(fp)) != -1) {
        ++size;
        if (dump && size <= 100) putchar(c);
    }
    if (dump) putchar('\n');
    printf("read %ld bytes from %s\n", size, paths[i]);

    fclose(fp);

#ifdef __EMSCRIPTEN__
    // Emscripten copies the contents of the dropped file into the
    // in-browser filesystem. Delete after usage to free up memory.
    printf("unlinking %s\n", paths[i]);
    unlink(paths[i]);
#endif

  }
#ifdef REPORT_RESULT
  REPORT_RESULT(1);
#endif
}