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
typedef  int /*<<< orphan*/  e_type ;

/* Variables and functions */
#define  ADDR 133 
#define  CREG 132 
#define  DREG 131 
#define  GREG 130 
#define  IMMED 129 
#define  INSN 128 
 int /*<<< orphan*/  e_addr ; 
 int /*<<< orphan*/  e_creg ; 
 int /*<<< orphan*/  e_dreg ; 
 int /*<<< orphan*/  e_greg ; 
 int /*<<< orphan*/  e_immed ; 
 int /*<<< orphan*/  e_insn ; 
 int /*<<< orphan*/  e_invtype ; 

__attribute__((used)) static e_type
get_type (int yytype)
{
  switch (yytype)
    {
      /* translate from yacc's type to enum */
    case INSN:
      return e_insn;
    case DREG:
      return e_dreg;
    case CREG:
      return e_creg;
    case GREG:
      return e_greg;
    case ADDR:
      return e_addr;
    case IMMED:
      return e_immed;
    default:
      return e_invtype;		/* error; invalid type */
    }
}