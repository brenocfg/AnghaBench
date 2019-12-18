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
struct target_ops {int dummy; } ;
typedef  enum target_object { ____Placeholder_target_object } target_object ;
typedef  int /*<<< orphan*/  ULONGEST ;
typedef  int LONGEST ;

/* Variables and functions */
 int NATIVE_XFER_AUXV (struct target_ops*,int,char const*,void*,void const*,int /*<<< orphan*/ ,int) ; 
 int NATIVE_XFER_DIRTY (struct target_ops*,int,char const*,void*,void const*,int /*<<< orphan*/ ,int) ; 
 int NATIVE_XFER_UNWIND_TABLE (struct target_ops*,int,char const*,void*,void const*,int /*<<< orphan*/ ,int) ; 
 int NATIVE_XFER_WCOOKIE (struct target_ops*,int,char const*,void*,void const*,int /*<<< orphan*/ ,int) ; 
#define  TARGET_OBJECT_AUXV 132 
#define  TARGET_OBJECT_DIRTY 131 
#define  TARGET_OBJECT_MEMORY 130 
#define  TARGET_OBJECT_UNWIND_TABLE 129 
#define  TARGET_OBJECT_WCOOKIE 128 
 int child_xfer_memory (int /*<<< orphan*/ ,void*,int,int,int /*<<< orphan*/ *,struct target_ops*) ; 

__attribute__((used)) static LONGEST
child_xfer_partial (struct target_ops *ops, enum target_object object,
		    const char *annex, void *readbuf,
		    const void *writebuf, ULONGEST offset, LONGEST len)
{
  switch (object)
    {
    case TARGET_OBJECT_MEMORY:
      if (readbuf)
	return child_xfer_memory (offset, readbuf, len, 0/*write*/,
				  NULL, ops);
      if (writebuf)
	return child_xfer_memory (offset, readbuf, len, 1/*write*/,
				  NULL, ops);
      return -1;

    case TARGET_OBJECT_UNWIND_TABLE:
#ifndef NATIVE_XFER_UNWIND_TABLE
#define NATIVE_XFER_UNWIND_TABLE(OPS,OBJECT,ANNEX,WRITEBUF,READBUF,OFFSET,LEN) (-1)
#endif
      return NATIVE_XFER_UNWIND_TABLE (ops, object, annex, readbuf, writebuf,
				       offset, len);

    case TARGET_OBJECT_AUXV:
#ifndef NATIVE_XFER_AUXV
#define NATIVE_XFER_AUXV(OPS,OBJECT,ANNEX,WRITEBUF,READBUF,OFFSET,LEN) (-1)
#endif
      return NATIVE_XFER_AUXV (ops, object, annex, readbuf, writebuf,
			       offset, len);

    case TARGET_OBJECT_WCOOKIE:
#ifndef NATIVE_XFER_WCOOKIE
#define NATIVE_XFER_WCOOKIE(OPS,OBJECT,ANNEX,WRITEBUF,READBUF,OFFSET,LEN) (-1)
#endif
      return NATIVE_XFER_WCOOKIE (ops, object, annex, readbuf, writebuf,
				  offset, len);

    case TARGET_OBJECT_DIRTY:
#ifndef NATIVE_XFER_DIRTY
#define NATIVE_XFER_DIRTY(OPS,OBJECT,ANNEX,WRITEBUF,READBUF,OFFSET,LEN) (-1)
#endif
      return NATIVE_XFER_DIRTY (ops, object, annex, readbuf, writebuf,
				offset, len);

    default:
      return -1;
    }
}