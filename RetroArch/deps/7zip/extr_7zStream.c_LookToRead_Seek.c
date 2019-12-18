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
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* Seek ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {TYPE_2__* realStream; scalar_t__ size; scalar_t__ pos; } ;
typedef  int /*<<< orphan*/  SRes ;
typedef  int /*<<< orphan*/  ESzSeek ;
typedef  TYPE_1__ CLookToRead ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static SRes LookToRead_Seek(void *pp, int64_t *pos, ESzSeek origin)
{
   CLookToRead *p = (CLookToRead *)pp;
   p->pos = p->size = 0;
   return p->realStream->Seek(p->realStream, pos, origin);
}