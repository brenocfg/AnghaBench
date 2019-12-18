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
typedef  int /*<<< orphan*/  cpp_token ;
struct TYPE_6__ {int /*<<< orphan*/  a_buff; } ;
typedef  TYPE_1__ cpp_reader ;
struct TYPE_7__ {int count; } ;
typedef  TYPE_2__ cpp_macro ;

/* Variables and functions */
 scalar_t__ BUFF_FRONT (int /*<<< orphan*/ ) ; 
 int BUFF_ROOM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _cpp_extend_buff (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static cpp_token *
alloc_expansion_token (cpp_reader *pfile, cpp_macro *macro)
{
  if (BUFF_ROOM (pfile->a_buff) < (macro->count + 1) * sizeof (cpp_token))
    _cpp_extend_buff (pfile, &pfile->a_buff, sizeof (cpp_token));

  return &((cpp_token *) BUFF_FRONT (pfile->a_buff))[macro->count++];
}