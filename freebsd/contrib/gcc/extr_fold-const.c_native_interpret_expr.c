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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
#define  BOOLEAN_TYPE 133 
#define  COMPLEX_TYPE 132 
#define  ENUMERAL_TYPE 131 
#define  INTEGER_TYPE 130 
 int /*<<< orphan*/  NULL_TREE ; 
#define  REAL_TYPE 129 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
#define  VECTOR_TYPE 128 
 int /*<<< orphan*/  native_interpret_complex (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  native_interpret_int (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  native_interpret_real (int /*<<< orphan*/ ,unsigned char*,int) ; 
 int /*<<< orphan*/  native_interpret_vector (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static tree
native_interpret_expr (tree type, unsigned char *ptr, int len)
{
  switch (TREE_CODE (type))
    {
    case INTEGER_TYPE:
    case ENUMERAL_TYPE:
    case BOOLEAN_TYPE:
      return native_interpret_int (type, ptr, len);

    case REAL_TYPE:
      return native_interpret_real (type, ptr, len);

    case COMPLEX_TYPE:
      return native_interpret_complex (type, ptr, len);

    case VECTOR_TYPE:
      return native_interpret_vector (type, ptr, len);

    default:
      return NULL_TREE;
    }
}