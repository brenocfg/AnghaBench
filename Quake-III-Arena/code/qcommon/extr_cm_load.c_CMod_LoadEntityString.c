#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  filelen; scalar_t__ fileofs; } ;
typedef  TYPE_1__ lump_t ;
struct TYPE_5__ {int /*<<< orphan*/  entityString; int /*<<< orphan*/  numEntityChars; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memcpy (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hunk_Alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ cm ; 
 scalar_t__ cmod_base ; 
 int /*<<< orphan*/  h_high ; 

void CMod_LoadEntityString( lump_t *l ) {
	cm.entityString = Hunk_Alloc( l->filelen, h_high );
	cm.numEntityChars = l->filelen;
	Com_Memcpy (cm.entityString, cmod_base + l->fileofs, l->filelen);
}