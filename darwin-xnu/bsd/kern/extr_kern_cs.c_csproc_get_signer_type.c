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
struct proc {int dummy; } ;
struct cs_blob {int dummy; } ;

/* Variables and functions */
 unsigned int CS_SIGNER_TYPE_UNKNOWN ; 
 unsigned int csblob_get_signer_type (struct cs_blob*) ; 
 struct cs_blob* csproc_get_blob (struct proc*) ; 

unsigned int
csproc_get_signer_type(struct proc *p)
{
	struct cs_blob *csblob;

	csblob = csproc_get_blob(p);
	if (csblob == NULL)
	    return CS_SIGNER_TYPE_UNKNOWN;

	return csblob_get_signer_type(csblob);
}