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

/* Variables and functions */
 int /*<<< orphan*/  REPORT_RESULT (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emscripten_wget_data (char const*,void**,int*,int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 void* strstr (void*,char*) ; 

int main()
{
    const char * file = "/test.txt";
    void* buffer;
    int num, error;

    printf("load %s\n", file);
    emscripten_wget_data(file, &buffer, &num, &error);
    assert(!error);
    assert(strstr(buffer, "emscripten") == buffer); 

    printf("load non-existing\n");
    emscripten_wget_data("doesnotexist", &buffer, &num, &error);
    assert(error);

    printf("ok!\n");
    REPORT_RESULT(1);
    return 0;
}