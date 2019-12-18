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
struct TYPE_4__ {scalar_t__ type; scalar_t__ host; scalar_t__ service; scalar_t__ proto; struct TYPE_4__* next; } ;
typedef  TYPE_1__ mdns_out_question_t ;

/* Variables and functions */

__attribute__((used)) static bool _mdns_question_exists(mdns_out_question_t * needle, mdns_out_question_t * haystack)
{
    while (haystack) {
        if (haystack->type == needle->type
            && haystack->host == needle->host
            && haystack->service == needle->service
            && haystack->proto == needle->proto) {
            return true;
        }
        haystack = haystack->next;
    }
    return false;
}