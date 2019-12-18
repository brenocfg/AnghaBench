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
typedef  void* u16_t ;
struct pbuf {scalar_t__ payload; void* len; int /*<<< orphan*/  type_internal; int /*<<< orphan*/ * next; void* tot_len; } ;
typedef  int /*<<< orphan*/  pbuf_type ;
typedef  int /*<<< orphan*/  pbuf_layer ;

/* Variables and functions */
 void* MEMP_PBUF_POOL ; 
 int /*<<< orphan*/  PBUF_POOL ; 
 scalar_t__ malloc (void*) ; 

struct pbuf * pbuf_alloc(pbuf_layer layer, u16_t length, pbuf_type type)
{
    struct pbuf * p;
    p = (struct pbuf *)malloc(MEMP_PBUF_POOL);
    p->tot_len = length;
    p->next = NULL;
    p->type_internal = PBUF_POOL;
    p->len = length;
    p->payload = malloc(length);
    return p;
}