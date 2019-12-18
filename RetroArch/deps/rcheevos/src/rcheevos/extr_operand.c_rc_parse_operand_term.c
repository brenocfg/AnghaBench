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
typedef  int /*<<< orphan*/  rc_parse_state_t ;
struct TYPE_6__ {unsigned int num; int /*<<< orphan*/  dbl; } ;
struct TYPE_7__ {void* type; TYPE_1__ value; } ;
typedef  TYPE_2__ rc_operand_t ;

/* Variables and functions */
 int RC_INVALID_CONST_OPERAND ; 
 int RC_INVALID_FP_OPERAND ; 
 int RC_OK ; 
 void* RC_OPERAND_CONST ; 
 void* RC_OPERAND_FP ; 
 int /*<<< orphan*/  floor (int /*<<< orphan*/ ) ; 
 int rc_parse_operand_lua (TYPE_2__*,char const**,int /*<<< orphan*/ *) ; 
 int rc_parse_operand_memory (TYPE_2__*,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strtod (char const*,char**) ; 
 unsigned long strtoul (char const*,char**,int) ; 

__attribute__((used)) static int rc_parse_operand_term(rc_operand_t* self, const char** memaddr, rc_parse_state_t* parse) {
  const char* aux = *memaddr;
  char* end;
  int ret;
  unsigned long value;

  switch (*aux) {
    case 'h': case 'H':
      value = strtoul(++aux, &end, 16);

      if (end == aux) {
        return RC_INVALID_CONST_OPERAND;
      }

      if (value > 0xffffffffU) {
        value = 0xffffffffU;
      }

      self->type = RC_OPERAND_CONST;
      self->value.num = (unsigned)value;

      aux = end;
      break;
    
    case 'v': case 'V':
      value = strtoul(++aux, &end, 10);

      if (end == aux) {
        return RC_INVALID_CONST_OPERAND;
      }

      if (value > 0xffffffffU) {
        value = 0xffffffffU;
      }

      self->type = RC_OPERAND_CONST;
      self->value.num = (unsigned)value;

      aux = end;
      break;
    
    case '0':
      if (aux[1] == 'x' || aux[1] == 'X') {
        /* fall through */
    default:
        ret = rc_parse_operand_memory(self, &aux, parse);

        if (ret < 0) {
          return ret;
        }

        break;
      }

      /* fall through */
    case '.':
    case '+': case '-':
    case '1': case '2': case '3': case '4': case '5':
    case '6': case '7': case '8': case '9':
      self->value.dbl = strtod(aux, &end);

      if (end == aux) {
        return RC_INVALID_FP_OPERAND;
      }

      if (floor(self->value.dbl) == self->value.dbl) {
        self->type = RC_OPERAND_CONST;
        self->value.num = (unsigned)floor(self->value.dbl);
      }
      else {
        self->type = RC_OPERAND_FP;
      }
      aux = end;
      break;
    
    case '@':
      ret = rc_parse_operand_lua(self, &aux, parse);

      if (ret < 0) {
        return ret;
      }

      break;
  }

  *memaddr = aux;
  return RC_OK;
}