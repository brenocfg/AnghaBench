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
typedef  int u8_t ;
struct pbuf {struct pbuf* payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct pbuf*) ; 

u8_t pbuf_free(struct pbuf *p)
{
    if (p) {
        if (p->payload) {
            free(p->payload);
            p->payload = NULL;
        }
        free (p);
        p = NULL;
    }
    return 1;
}