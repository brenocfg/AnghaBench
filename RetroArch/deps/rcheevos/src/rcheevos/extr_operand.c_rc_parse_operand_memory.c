#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ offset; } ;
typedef  TYPE_2__ rc_parse_state_t ;
struct TYPE_7__ {int /*<<< orphan*/  memref; } ;
struct TYPE_9__ {TYPE_1__ value; void* type; } ;
typedef  TYPE_3__ rc_operand_t ;

/* Variables and functions */
 int RC_INVALID_MEMORY_OPERAND ; 
 char RC_MEMSIZE_16_BITS ; 
 char RC_MEMSIZE_24_BITS ; 
 char RC_MEMSIZE_32_BITS ; 
 char RC_MEMSIZE_8_BITS ; 
 char RC_MEMSIZE_BIT_0 ; 
 char RC_MEMSIZE_BIT_1 ; 
 char RC_MEMSIZE_BIT_2 ; 
 char RC_MEMSIZE_BIT_3 ; 
 char RC_MEMSIZE_BIT_4 ; 
 char RC_MEMSIZE_BIT_5 ; 
 char RC_MEMSIZE_BIT_6 ; 
 char RC_MEMSIZE_BIT_7 ; 
 char RC_MEMSIZE_HIGH ; 
 char RC_MEMSIZE_LOW ; 
 int RC_OK ; 
 void* RC_OPERAND_ADDRESS ; 
 void* RC_OPERAND_DELTA ; 
 void* RC_OPERAND_PRIOR ; 
 int /*<<< orphan*/  rc_alloc_memref_value (TYPE_2__*,unsigned int,char,char) ; 
 unsigned long strtoul (char const*,char**,int) ; 

__attribute__((used)) static int rc_parse_operand_memory(rc_operand_t* self, const char** memaddr, rc_parse_state_t* parse) {
  const char* aux = *memaddr;
  char* end;
  unsigned long address;
  char is_bcd = 0;
  char size;

  switch (*aux++) {
    case 'd': case 'D':
      self->type = RC_OPERAND_DELTA;
      break;

    case 'b': case 'B':
      self->type = RC_OPERAND_ADDRESS;
      is_bcd = 1;
      break;

    case 'p': case 'P':
      self->type = RC_OPERAND_PRIOR;
      break;

    default:
      self->type = RC_OPERAND_ADDRESS;
      aux--;
      break;
  }

  if (*aux++ != '0') {
    return RC_INVALID_MEMORY_OPERAND;
  }

  if (*aux != 'x' && *aux != 'X') {
    return RC_INVALID_MEMORY_OPERAND;
  }

  aux++;

  switch (*aux++) {
    case 'm': case 'M': size = RC_MEMSIZE_BIT_0; break;
    case 'n': case 'N': size = RC_MEMSIZE_BIT_1; break;
    case 'o': case 'O': size = RC_MEMSIZE_BIT_2; break;
    case 'p': case 'P': size = RC_MEMSIZE_BIT_3; break;
    case 'q': case 'Q': size = RC_MEMSIZE_BIT_4; break;
    case 'r': case 'R': size = RC_MEMSIZE_BIT_5; break;
    case 's': case 'S': size = RC_MEMSIZE_BIT_6; break;
    case 't': case 'T': size = RC_MEMSIZE_BIT_7; break;
    case 'l': case 'L': size = RC_MEMSIZE_LOW; break;
    case 'u': case 'U': size = RC_MEMSIZE_HIGH; break;
    case 'h': case 'H': size = RC_MEMSIZE_8_BITS; break;
    case 'w': case 'W': size = RC_MEMSIZE_24_BITS; break;
    case 'x': case 'X': size = RC_MEMSIZE_32_BITS; break;

    default: /* fall through */
      aux--;
    case ' ':
      size = RC_MEMSIZE_16_BITS;
      break;
  }

  address = strtoul(aux, &end, 16);

  if (end == aux) {
    return RC_INVALID_MEMORY_OPERAND;
  }

  if (address > 0xffffffffU) {
    address = 0xffffffffU;
  }

  self->value.memref = rc_alloc_memref_value(parse, (unsigned)address, size, is_bcd);
  if (parse->offset < 0)
    return parse->offset;

  *memaddr = end;
  return RC_OK;
}