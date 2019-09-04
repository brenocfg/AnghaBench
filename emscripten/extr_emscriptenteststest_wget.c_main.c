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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  REPORT_RESULT (int) ; 
 int /*<<< orphan*/  emscripten_wget (char const*,char const*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ strstr (char*,char*) ; 
 char tolower (char) ; 

int main()
{
    const char * file = "/test.txt";
    emscripten_wget(file , file);
    FILE * f = fopen(file, "r");
    int result = 0;
    if(f) {
#define BUFSIZE 1024
        char buf[BUFSIZE];
        fgets(buf, BUFSIZE, f);
        buf[BUFSIZE-1] = 0;
        for(int i = 0; i < BUFSIZE; ++i)
            buf[i] = tolower(buf[i]);
        if(strstr(buf, "emscripten")) 
            result = 1;
        fclose(f);
    }
    REPORT_RESULT(result);
    return 0;
}