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
struct objfile {int dummy; } ;
struct dieinfo {char* die; int die_ref; scalar_t__ die_length; void* die_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIE_ID ; 
 int /*<<< orphan*/  DIE_NAME ; 
 int /*<<< orphan*/  GET_UNSIGNED ; 
 scalar_t__ SIZEOF_DIE_LENGTH ; 
 scalar_t__ SIZEOF_DIE_TAG ; 
 void* TAG_padding ; 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dieinfo* curdie ; 
 char* dbbase ; 
 int dbroff ; 
 int dbsize ; 
 int /*<<< orphan*/  memset (struct dieinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  symfile_complaints ; 
 void* target_to_host (char*,scalar_t__,int /*<<< orphan*/ ,struct objfile*) ; 

__attribute__((used)) static void
basicdieinfo (struct dieinfo *dip, char *diep, struct objfile *objfile)
{
  curdie = dip;
  memset (dip, 0, sizeof (struct dieinfo));
  dip->die = diep;
  dip->die_ref = dbroff + (diep - dbbase);
  dip->die_length = target_to_host (diep, SIZEOF_DIE_LENGTH, GET_UNSIGNED,
				    objfile);
  if ((dip->die_length < SIZEOF_DIE_LENGTH) ||
      ((diep + dip->die_length) > (dbbase + dbsize)))
    {
      complaint (&symfile_complaints,
		 "DIE @ 0x%x \"%s\", malformed DIE, bad length (%ld bytes)",
		 DIE_ID, DIE_NAME, dip->die_length);
      dip->die_length = 0;
    }
  else if (dip->die_length < (SIZEOF_DIE_LENGTH + SIZEOF_DIE_TAG))
    {
      dip->die_tag = TAG_padding;
    }
  else
    {
      diep += SIZEOF_DIE_LENGTH;
      dip->die_tag = target_to_host (diep, SIZEOF_DIE_TAG, GET_UNSIGNED,
				     objfile);
    }
}