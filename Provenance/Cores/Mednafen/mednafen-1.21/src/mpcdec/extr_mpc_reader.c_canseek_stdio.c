#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ magic; int /*<<< orphan*/  is_seekable; } ;
typedef  TYPE_1__ mpc_reader_stdio ;
struct TYPE_5__ {scalar_t__ data; } ;
typedef  TYPE_2__ mpc_reader ;
typedef  int /*<<< orphan*/  mpc_bool_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPC_FALSE ; 
 scalar_t__ STDIO_MAGIC ; 

__attribute__((used)) static mpc_bool_t
canseek_stdio(mpc_reader *p_reader)
{
    mpc_reader_stdio *p_stdio = (mpc_reader_stdio*) p_reader->data;
    if(p_stdio->magic != STDIO_MAGIC) return MPC_FALSE;
    return p_stdio->is_seekable;
}