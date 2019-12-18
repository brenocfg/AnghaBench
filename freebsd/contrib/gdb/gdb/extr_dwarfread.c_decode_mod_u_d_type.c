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

/* Variables and functions */
 int /*<<< orphan*/  AT_mod_u_d_type ; 
 int /*<<< orphan*/  AT_user_def_type ; 
 int /*<<< orphan*/  GET_UNSIGNED ; 
 unsigned short attribute_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_objfile ; 
 struct type* decode_modified_type (char*,unsigned short,int /*<<< orphan*/ ) ; 
 unsigned short target_to_host (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct type *
decode_mod_u_d_type (char *typedata)
{
  struct type *typep = NULL;
  unsigned short modcount;
  int nbytes;

  /* Get the total size of the block, exclusive of the size itself */

  nbytes = attribute_size (AT_mod_u_d_type);
  modcount = target_to_host (typedata, nbytes, GET_UNSIGNED, current_objfile);
  typedata += nbytes;

  /* Deduct the size of the reference type bytes at the end of the block. */

  modcount -= attribute_size (AT_user_def_type);

  /* Now do the actual decoding */

  typep = decode_modified_type (typedata, modcount, AT_mod_u_d_type);
  return (typep);
}