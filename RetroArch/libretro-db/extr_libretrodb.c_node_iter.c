#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct node_iter_ctx {TYPE_2__* idx; TYPE_1__* db; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {scalar_t__ key_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 scalar_t__ filestream_write (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int node_iter(void *value, void *ctx)
{
   struct node_iter_ctx *nictx = (struct node_iter_ctx*)ctx;

   if (filestream_write(nictx->db->fd, value,
            (ssize_t)(nictx->idx->key_size + sizeof(uint64_t))) > 0)
      return 0;

   return -1;
}