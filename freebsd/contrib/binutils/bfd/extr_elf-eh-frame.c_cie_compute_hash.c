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
struct cie {int /*<<< orphan*/  hash; scalar_t__ initial_insn_length; int /*<<< orphan*/  initial_instructions; scalar_t__ fde_encoding; scalar_t__ lsda_encoding; scalar_t__ per_encoding; scalar_t__ output_sec; scalar_t__ personality; scalar_t__ augmentation_size; scalar_t__ ra_column; scalar_t__ data_align; scalar_t__ code_align; int /*<<< orphan*/  augmentation; scalar_t__ version; scalar_t__ length; } ;
typedef  int /*<<< orphan*/  hashval_t ;

/* Variables and functions */
 int /*<<< orphan*/  iterative_hash (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iterative_hash_object (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static hashval_t
cie_compute_hash (struct cie *c)
{
  hashval_t h = 0;
  h = iterative_hash_object (c->length, h);
  h = iterative_hash_object (c->version, h);
  h = iterative_hash (c->augmentation, strlen (c->augmentation) + 1, h);
  h = iterative_hash_object (c->code_align, h);
  h = iterative_hash_object (c->data_align, h);
  h = iterative_hash_object (c->ra_column, h);
  h = iterative_hash_object (c->augmentation_size, h);
  h = iterative_hash_object (c->personality, h);
  h = iterative_hash_object (c->output_sec, h);
  h = iterative_hash_object (c->per_encoding, h);
  h = iterative_hash_object (c->lsda_encoding, h);
  h = iterative_hash_object (c->fde_encoding, h);
  h = iterative_hash_object (c->initial_insn_length, h);
  h = iterative_hash (c->initial_instructions, c->initial_insn_length, h);
  c->hash = h;
  return h;
}