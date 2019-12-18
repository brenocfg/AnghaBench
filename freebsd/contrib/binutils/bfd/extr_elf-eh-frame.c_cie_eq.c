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
struct cie {scalar_t__ hash; scalar_t__ length; scalar_t__ version; scalar_t__ local_personality; char* augmentation; scalar_t__ code_align; scalar_t__ data_align; scalar_t__ ra_column; scalar_t__ augmentation_size; scalar_t__ output_sec; scalar_t__ per_encoding; scalar_t__ lsda_encoding; scalar_t__ fde_encoding; int initial_insn_length; int /*<<< orphan*/ * initial_instructions; int /*<<< orphan*/  personality; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
cie_eq (const void *e1, const void *e2)
{
  const struct cie *c1 = e1;
  const struct cie *c2 = e2;

  if (c1->hash == c2->hash
      && c1->length == c2->length
      && c1->version == c2->version
      && c1->local_personality == c2->local_personality
      && strcmp (c1->augmentation, c2->augmentation) == 0
      && strcmp (c1->augmentation, "eh") != 0
      && c1->code_align == c2->code_align
      && c1->data_align == c2->data_align
      && c1->ra_column == c2->ra_column
      && c1->augmentation_size == c2->augmentation_size
      && memcmp (&c1->personality, &c2->personality,
		 sizeof (c1->personality)) == 0
      && c1->output_sec == c2->output_sec
      && c1->per_encoding == c2->per_encoding
      && c1->lsda_encoding == c2->lsda_encoding
      && c1->fde_encoding == c2->fde_encoding
      && c1->initial_insn_length == c2->initial_insn_length
      && memcmp (c1->initial_instructions,
		 c2->initial_instructions,
		 c1->initial_insn_length) == 0)
    return 1;

  return 0;
}