#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct target_ops {int (* to_xfer_memory ) (int /*<<< orphan*/ ,void*,int,int,int /*<<< orphan*/ *,struct target_ops*) ;TYPE_1__* beneath; } ;
typedef  enum target_object { ____Placeholder_target_object } target_object ;
typedef  int /*<<< orphan*/  ULONGEST ;
struct TYPE_2__ {int (* to_xfer_partial ) (TYPE_1__*,int,char const*,void*,void const*,int /*<<< orphan*/ ,int) ;} ;
typedef  int LONGEST ;

/* Variables and functions */
#define  TARGET_OBJECT_AUXV 129 
#define  TARGET_OBJECT_MEMORY 128 
 int procfs_xfer_auxv (struct target_ops*,int,char const*,void*,void const*,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ,void*,int,int,int /*<<< orphan*/ *,struct target_ops*) ; 
 int stub2 (int /*<<< orphan*/ ,void*,int,int,int /*<<< orphan*/ *,struct target_ops*) ; 
 int stub3 (TYPE_1__*,int,char const*,void*,void const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static LONGEST
procfs_xfer_partial (struct target_ops *ops, enum target_object object,
		     const char *annex, void *readbuf,
		     const void *writebuf, ULONGEST offset, LONGEST len)
{
  switch (object)
    {
    case TARGET_OBJECT_MEMORY:
      if (readbuf)
	return (*ops->to_xfer_memory) (offset, readbuf, len, 0/*write*/,
				       NULL, ops);
      if (writebuf)
	return (*ops->to_xfer_memory) (offset, readbuf, len, 1/*write*/,
				       NULL, ops);
      return -1;

#ifdef NEW_PROC_API
    case TARGET_OBJECT_AUXV:
      return procfs_xfer_auxv (ops, object, annex, readbuf, writebuf,
			       offset, len);
#endif

    default:
      if (ops->beneath != NULL)
	return ops->beneath->to_xfer_partial (ops->beneath, object, annex,
					      readbuf, writebuf, offset, len);
      return -1;
    }
}