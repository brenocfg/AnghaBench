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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct cs_blob {int csb_flags; int /*<<< orphan*/  csb_mem_size; scalar_t__ csb_mem_kaddr; } ;
typedef  int /*<<< orphan*/  CS_GenericBlob ;

/* Variables and functions */
 int CS_VALID ; 
 int /*<<< orphan*/  const* csblob_find_blob_bytes (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

const CS_GenericBlob *
csblob_find_blob(struct cs_blob *csblob, uint32_t type, uint32_t magic)
{
	if ((csblob->csb_flags & CS_VALID) == 0)
		return NULL;
	return csblob_find_blob_bytes((const uint8_t *)csblob->csb_mem_kaddr, csblob->csb_mem_size, type, magic);
}