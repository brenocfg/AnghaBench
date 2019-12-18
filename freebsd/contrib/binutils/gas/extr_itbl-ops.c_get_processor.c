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
typedef  int /*<<< orphan*/  e_processor ;

/* Variables and functions */
 int /*<<< orphan*/  e_invproc ; 
 int e_nprocs ; 
 int e_p0 ; 

__attribute__((used)) static e_processor
get_processor (int yyproc)
{
  /* translate from yacc's processor to enum */
  if (yyproc >= e_p0 && yyproc < e_nprocs)
    return (e_processor) yyproc;
  return e_invproc;		/* error; invalid processor */
}