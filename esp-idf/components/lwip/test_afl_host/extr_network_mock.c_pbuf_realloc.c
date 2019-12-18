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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  void* u16_t ;
struct pbuf {void* tot_len; void* len; int /*<<< orphan*/ * payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (void*) ; 

void pbuf_realloc(struct pbuf *p, u16_t size)
{
    if (p != NULL)
    {
        uint8_t *buf = malloc(size);
        free(p->payload);
        p->payload = buf;
        p->len = size;
        p->tot_len = size;
    }
}