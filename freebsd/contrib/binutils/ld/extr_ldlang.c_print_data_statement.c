#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int type; TYPE_5__* exp; int /*<<< orphan*/  value; TYPE_1__* output_section; scalar_t__ output_offset; } ;
typedef  TYPE_3__ lang_data_statement_type ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_size_type ;
struct TYPE_7__ {scalar_t__ node_class; } ;
struct TYPE_9__ {TYPE_2__ type; } ;
struct TYPE_6__ {scalar_t__ vma; } ;

/* Variables and functions */
#define  BYTE 132 
 int /*<<< orphan*/  BYTE_SIZE ; 
#define  LONG 131 
 int /*<<< orphan*/  LONG_SIZE ; 
#define  QUAD 130 
 int /*<<< orphan*/  QUAD_SIZE ; 
 int SECTION_NAME_MAP_LENGTH ; 
#define  SHORT 129 
 int /*<<< orphan*/  SHORT_SIZE ; 
#define  SQUAD 128 
 scalar_t__ TO_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ etree_value ; 
 int /*<<< orphan*/  exp_print_tree (TYPE_5__*) ; 
 int /*<<< orphan*/  init_opb () ; 
 int /*<<< orphan*/  minfo (char*,scalar_t__,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ print_dot ; 
 int /*<<< orphan*/  print_nl () ; 
 int /*<<< orphan*/  print_space () ; 

__attribute__((used)) static void
print_data_statement (lang_data_statement_type *data)
{
  int i;
  bfd_vma addr;
  bfd_size_type size;
  const char *name;

  init_opb ();
  for (i = 0; i < SECTION_NAME_MAP_LENGTH; i++)
    print_space ();

  addr = data->output_offset;
  if (data->output_section != NULL)
    addr += data->output_section->vma;

  switch (data->type)
    {
    default:
      abort ();
    case BYTE:
      size = BYTE_SIZE;
      name = "BYTE";
      break;
    case SHORT:
      size = SHORT_SIZE;
      name = "SHORT";
      break;
    case LONG:
      size = LONG_SIZE;
      name = "LONG";
      break;
    case QUAD:
      size = QUAD_SIZE;
      name = "QUAD";
      break;
    case SQUAD:
      size = QUAD_SIZE;
      name = "SQUAD";
      break;
    }

  minfo ("0x%V %W %s 0x%v", addr, size, name, data->value);

  if (data->exp->type.node_class != etree_value)
    {
      print_space ();
      exp_print_tree (data->exp);
    }

  print_nl ();

  print_dot = addr + TO_ADDR (size);
}