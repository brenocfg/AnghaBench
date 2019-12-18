#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gcc_pointer ;
struct TYPE_3__ {size_t size; int /*<<< orphan*/  value; int /*<<< orphan*/  align; } ;
typedef  TYPE_1__ __emutls_control ;

/* Variables and functions */
 int /*<<< orphan*/  COMPILE_TIME_ASSERT (int) ; 
 int /*<<< orphan*/  abort () ; 
 void* emutls_memalign_alloc (size_t,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static __inline void *emutls_allocate_object(__emutls_control *control) {
  // Use standard C types, check with gcc's emutls.o.
  COMPILE_TIME_ASSERT(sizeof(uintptr_t) == sizeof(gcc_pointer));
  COMPILE_TIME_ASSERT(sizeof(uintptr_t) == sizeof(void *));

  size_t size = control->size;
  size_t align = control->align;
  void *base;
  if (align < sizeof(void *))
    align = sizeof(void *);
  // Make sure that align is power of 2.
  if ((align & (align - 1)) != 0)
    abort();

  base = emutls_memalign_alloc(align, size);
  if (control->value)
    memcpy(base, control->value, size);
  else
    memset(base, 0, size);
  return base;
}