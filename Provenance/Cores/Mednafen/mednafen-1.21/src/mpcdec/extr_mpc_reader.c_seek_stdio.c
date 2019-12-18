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
struct TYPE_4__ {scalar_t__ magic; int /*<<< orphan*/  p_file; scalar_t__ is_seekable; } ;
typedef  TYPE_1__ mpc_reader_stdio ;
struct TYPE_5__ {scalar_t__ data; } ;
typedef  TYPE_2__ mpc_reader ;
typedef  int /*<<< orphan*/  mpc_int32_t ;
typedef  int mpc_bool_t ;

/* Variables and functions */
 int MPC_FALSE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ STDIO_MAGIC ; 
 scalar_t__ fseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mpc_bool_t
seek_stdio(mpc_reader *p_reader, mpc_int32_t offset)
{
    mpc_reader_stdio *p_stdio = (mpc_reader_stdio*) p_reader->data;
    if(p_stdio->magic != STDIO_MAGIC) return MPC_FALSE;
    return p_stdio->is_seekable ? fseek(p_stdio->p_file, offset, SEEK_SET) == 0 : MPC_FALSE;
}