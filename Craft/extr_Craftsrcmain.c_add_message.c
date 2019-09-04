#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t message_index; int /*<<< orphan*/ * messages; } ;

/* Variables and functions */
 int MAX_MESSAGES ; 
 int /*<<< orphan*/  MAX_TEXT_LENGTH ; 
 TYPE_1__* g ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*) ; 

void add_message(const char *text) {
    printf("%s\n", text);
    snprintf(
        g->messages[g->message_index], MAX_TEXT_LENGTH, "%s", text);
    g->message_index = (g->message_index + 1) % MAX_MESSAGES;
}