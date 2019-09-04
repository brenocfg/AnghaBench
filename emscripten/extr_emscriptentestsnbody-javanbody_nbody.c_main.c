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
typedef  int /*<<< orphan*/  java_lang_Thread ;
typedef  int /*<<< orphan*/  JAVA_OBJECT ;

/* Variables and functions */
 scalar_t__ XMLVM_SETJMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * java_lang_Thread_currentThread__ () ; 
 int /*<<< orphan*/  nbody_nbody_main___java_lang_String_1ARRAY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  xmlvm_create_java_string_array (int,char**) ; 
 int /*<<< orphan*/  xmlvm_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlvm_exception_env_main_thread ; 
 int /*<<< orphan*/  xmlvm_init () ; 
 int /*<<< orphan*/  xmlvm_unhandled_exception () ; 

int main(int argc, char* argv[])
{
    // translate our normalized argument (0-0, 1-0.1secs, 2-0.5secs, 3-1sec, 4-5secs, 5-10secs) to nbody
    int arg = argc > 1 ? argv[1][0] - '0' : 3;
    char buffer[100];
    argv[1] = buffer;
    int n;
    switch(arg) {
      case 0: return 0; break;
      case 1: n = 600000; break;
      case 2: n = 3600000; break;
      case 3: n = 6550000; break;
      case 4: n = 30000000; break;
      case 5: n = 60000000; break;
      default: printf("error: %d\\n", arg); return -1;
    }
    snprintf(buffer, 50, "%d", n);

    xmlvm_init();

    // Initialize the main thread before entering XMLVM_SETJMP
    java_lang_Thread* mainThread = java_lang_Thread_currentThread__();
    if (XMLVM_SETJMP(xmlvm_exception_env_main_thread)) {
        // Technically, XMLVM_UNWIND_EXCEPTION() should be called, but
        // exceptions will not be used anymore and XMLVM_ENTER_METHOD() wasn't
        // called (excessive), so a compilation error would occur

        xmlvm_unhandled_exception();
    } else {
        // Convert command-line args to String[]. First C-arg is omitted.
        JAVA_OBJECT args = xmlvm_create_java_string_array(argc-1, argv+1);
        nbody_nbody_main___java_lang_String_1ARRAY(args);
    }

    xmlvm_destroy(mainThread);

    return 0;
}