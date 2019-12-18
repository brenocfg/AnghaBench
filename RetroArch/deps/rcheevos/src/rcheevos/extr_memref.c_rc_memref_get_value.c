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
typedef  int (* rc_peek_t ) (int /*<<< orphan*/ ,int,void*) ;
struct TYPE_3__ {int size; int /*<<< orphan*/  is_bcd; int /*<<< orphan*/  address; } ;
typedef  TYPE_1__ rc_memref_t ;

/* Variables and functions */
#define  RC_MEMSIZE_16_BITS 141 
#define  RC_MEMSIZE_24_BITS 140 
#define  RC_MEMSIZE_32_BITS 139 
#define  RC_MEMSIZE_8_BITS 138 
#define  RC_MEMSIZE_BIT_0 137 
#define  RC_MEMSIZE_BIT_1 136 
#define  RC_MEMSIZE_BIT_2 135 
#define  RC_MEMSIZE_BIT_3 134 
#define  RC_MEMSIZE_BIT_4 133 
#define  RC_MEMSIZE_BIT_5 132 
#define  RC_MEMSIZE_BIT_6 131 
#define  RC_MEMSIZE_BIT_7 130 
#define  RC_MEMSIZE_HIGH 129 
#define  RC_MEMSIZE_LOW 128 

__attribute__((used)) static unsigned rc_memref_get_value(rc_memref_t* self, rc_peek_t peek, void* ud) {
  unsigned value;

  switch (self->size)
  {
    case RC_MEMSIZE_BIT_0:
      value = (peek(self->address, 1, ud) >> 0) & 1;
      break;

    case RC_MEMSIZE_BIT_1:
      value = (peek(self->address, 1, ud) >> 1) & 1;
      break;

    case RC_MEMSIZE_BIT_2:
      value = (peek(self->address, 1, ud) >> 2) & 1;
      break;

    case RC_MEMSIZE_BIT_3:
      value = (peek(self->address, 1, ud) >> 3) & 1;
      break;

    case RC_MEMSIZE_BIT_4:
      value = (peek(self->address, 1, ud) >> 4) & 1;
      break;

    case RC_MEMSIZE_BIT_5:
      value = (peek(self->address, 1, ud) >> 5) & 1;
      break;

    case RC_MEMSIZE_BIT_6:
      value = (peek(self->address, 1, ud) >> 6) & 1;
      break;

    case RC_MEMSIZE_BIT_7:
      value = (peek(self->address, 1, ud) >> 7) & 1;
      break;

    case RC_MEMSIZE_LOW:
      value = peek(self->address, 1, ud) & 0x0f;
      break;

    case RC_MEMSIZE_HIGH:
      value = (peek(self->address, 1, ud) >> 4) & 0x0f;
      break;

    case RC_MEMSIZE_8_BITS:
      value = peek(self->address, 1, ud);

      if (self->is_bcd) {
         value = ((value >> 4) & 0x0f) * 10 + (value & 0x0f);
      }

      break;

    case RC_MEMSIZE_16_BITS:
      value = peek(self->address, 2, ud);

      if (self->is_bcd) {
         value = ((value >> 12) & 0x0f) * 1000
               + ((value >> 8) & 0x0f) * 100
               + ((value >> 4) & 0x0f) * 10
               + ((value >> 0) & 0x0f) * 1;
      }

      break;

    case RC_MEMSIZE_24_BITS:
      value = peek(self->address, 4, ud);

      if (self->is_bcd) {
        value = ((value >> 20) & 0x0f) * 100000
              + ((value >> 16) & 0x0f) * 10000
              + ((value >> 12) & 0x0f) * 1000
              + ((value >> 8) & 0x0f) * 100
              + ((value >> 4) & 0x0f) * 10
              + ((value >> 0) & 0x0f) * 1;
      }

      break;

    case RC_MEMSIZE_32_BITS:
      value = peek(self->address, 4, ud);

      if (self->is_bcd) {
        value = ((value >> 28) & 0x0f) * 10000000
              + ((value >> 24) & 0x0f) * 1000000
              + ((value >> 20) & 0x0f) * 100000
              + ((value >> 16) & 0x0f) * 10000
              + ((value >> 12) & 0x0f) * 1000
              + ((value >> 8) & 0x0f) * 100
              + ((value >> 4) & 0x0f) * 10
              + ((value >> 0) & 0x0f) * 1;
      }

      break;

    default:
      value = 0;
      break;
  }

  return value;
}