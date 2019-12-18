#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int not_run; char const* name; struct TYPE_6__* next; scalar_t__ failed; scalar_t__ num_test; } ;
typedef  TYPE_1__ sub_suite ;
struct TYPE_7__ {TYPE_1__* tail; TYPE_1__* head; } ;
typedef  TYPE_2__ abts_suite ;

/* Variables and functions */
 int /*<<< orphan*/  calloc (int,int) ; 
 scalar_t__ curr_char ; 
 int /*<<< orphan*/  end_suite (TYPE_2__*) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ list_tests ; 
 void* malloc (int) ; 
 char const* memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  reset_status () ; 
 int /*<<< orphan*/  should_test_run (char*) ; 
 int /*<<< orphan*/  stdout ; 
 void* strrchr (char const*,char) ; 
 int /*<<< orphan*/  update_status () ; 

abts_suite *abts_add_suite(abts_suite *suite, const char *suite_name_full)
{
    sub_suite *subsuite;
    char *p;
    const char *suite_name;
    curr_char = 0;
    
    /* Only end the suite if we actually ran it */
    if (suite && suite->tail &&!suite->tail->not_run) {
        end_suite(suite);
    }

    subsuite = malloc(sizeof(*subsuite));
    subsuite->num_test = 0;
    subsuite->failed = 0;
    subsuite->next = NULL;
    /* suite_name_full may be an absolute path depending on __FILE__ 
     * expansion */
    suite_name = strrchr(suite_name_full, '/');
    if (!suite_name) {
        suite_name = strrchr(suite_name_full, '\\');
    }
    if (suite_name) {
        suite_name++;
    } else {
        suite_name = suite_name_full;
    }
    p = strrchr(suite_name, '.');
    if (p) {
        subsuite->name = memcpy(calloc(p - suite_name + 1, 1),
                                suite_name, p - suite_name);
    }
    else {
        subsuite->name = suite_name;
    }

    if (list_tests) {
        fprintf(stdout, "%s\n", subsuite->name);
    }
    
    subsuite->not_run = 0;

    if (suite == NULL) {
        suite = malloc(sizeof(*suite));
        suite->head = subsuite;
        suite->tail = subsuite;
    }
    else {
        suite->tail->next = subsuite;
        suite->tail = subsuite;
    }

    if (!should_test_run(subsuite->name)) {
        subsuite->not_run = 1;
        return suite;
    }

    reset_status();
    fprintf(stdout, "%-20s:  ", subsuite->name);
    update_status();
    fflush(stdout);

    return suite;
}