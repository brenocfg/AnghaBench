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
struct neon_type_el {int /*<<< orphan*/  size; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 unsigned int N_EQK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  neon_modify_type_size (unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct neon_type_el
neon_type_promote (struct neon_type_el *key, unsigned thisarg)
{
  struct neon_type_el dest = *key;
  
  assert ((thisarg & N_EQK) != 0);
  
  neon_modify_type_size (thisarg, &dest.type, &dest.size);

  return dest;
}