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
struct curl_llist {int /*<<< orphan*/ * tail; int /*<<< orphan*/ * head; int /*<<< orphan*/  dtor; scalar_t__ size; } ;
typedef  int /*<<< orphan*/  curl_llist_dtor ;

/* Variables and functions */

void
Curl_llist_init(struct curl_llist *l, curl_llist_dtor dtor)
{
  l->size = 0;
  l->dtor = dtor;
  l->head = NULL;
  l->tail = NULL;
}