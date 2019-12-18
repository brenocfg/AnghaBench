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
struct type {int dummy; } ;
typedef  enum amd64_reg_class { ____Placeholder_amd64_reg_class } amd64_reg_class ;

/* Variables and functions */
 int AMD64_MEMORY ; 
 int AMD64_NO_CLASS ; 
 int AMD64_SSE ; 
 int AMD64_SSEUP ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_ARRAY ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 scalar_t__ TYPE_CODE_UNION ; 
 int TYPE_FIELD_BITPOS (struct type*,int) ; 
 scalar_t__ TYPE_FIELD_STATIC (struct type*,int) ; 
 int /*<<< orphan*/  TYPE_FIELD_TYPE (struct type*,int) ; 
 int TYPE_LENGTH (struct type*) ; 
 int TYPE_NFIELDS (struct type*) ; 
 int /*<<< orphan*/  TYPE_TARGET_TYPE (struct type*) ; 
 int /*<<< orphan*/  amd64_classify (struct type*,int*) ; 
 int amd64_merge_classes (int,int) ; 
 scalar_t__ amd64_non_pod_p (struct type*) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_assert (int) ; 

__attribute__((used)) static void
amd64_classify_aggregate (struct type *type, enum amd64_reg_class class[2])
{
  int len = TYPE_LENGTH (type);

  /* 1. If the size of an object is larger than two eightbytes, or in
        C++, is a non-POD structure or union type, or contains
        unaligned fields, it has class memory.  */
  if (len > 16 || amd64_non_pod_p (type))
    {
      class[0] = class[1] = AMD64_MEMORY;
      return;
    }

  /* 2. Both eightbytes get initialized to class NO_CLASS.  */
  class[0] = class[1] = AMD64_NO_CLASS;

  /* 3. Each field of an object is classified recursively so that
        always two fields are considered. The resulting class is
        calculated according to the classes of the fields in the
        eightbyte: */

  if (TYPE_CODE (type) == TYPE_CODE_ARRAY)
    {
      struct type *subtype = check_typedef (TYPE_TARGET_TYPE (type));

      /* All fields in an array have the same type.  */
      amd64_classify (subtype, class);
      if (len > 8 && class[1] == AMD64_NO_CLASS)
	class[1] = class[0];
    }
  else
    {
      int i;

      /* Structure or union.  */
      gdb_assert (TYPE_CODE (type) == TYPE_CODE_STRUCT
		  || TYPE_CODE (type) == TYPE_CODE_UNION);

      for (i = 0; i < TYPE_NFIELDS (type); i++)
	{
	  struct type *subtype = check_typedef (TYPE_FIELD_TYPE (type, i));
	  int pos = TYPE_FIELD_BITPOS (type, i) / 64;
	  enum amd64_reg_class subclass[2];

	  /* Ignore static fields.  */
	  if (TYPE_FIELD_STATIC (type, i))
	    continue;

	  gdb_assert (pos == 0 || pos == 1);

	  amd64_classify (subtype, subclass);
	  class[pos] = amd64_merge_classes (class[pos], subclass[0]);
	  if (pos == 0)
	    class[1] = amd64_merge_classes (class[1], subclass[1]);
	}
    }

  /* 4. Then a post merger cleanup is done:  */

  /* Rule (a): If one of the classes is MEMORY, the whole argument is
     passed in memory.  */
  if (class[0] == AMD64_MEMORY || class[1] == AMD64_MEMORY)
    class[0] = class[1] = AMD64_MEMORY;

  /* Rule (b): If SSEUP is not preceeded by SSE, it is converted to
     SSE.  */
  if (class[0] == AMD64_SSEUP)
    class[0] = AMD64_SSE;
  if (class[1] == AMD64_SSEUP && class[0] != AMD64_SSE)
    class[1] = AMD64_SSE;
}