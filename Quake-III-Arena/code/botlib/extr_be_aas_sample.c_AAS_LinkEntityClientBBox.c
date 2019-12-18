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
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  aas_link_t ;

/* Variables and functions */
 int /*<<< orphan*/ * AAS_AASLinkEntity (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AAS_PresenceTypeBoundingBox (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

aas_link_t *AAS_LinkEntityClientBBox(vec3_t absmins, vec3_t absmaxs, int entnum, int presencetype)
{
	vec3_t mins, maxs;
	vec3_t newabsmins, newabsmaxs;

	AAS_PresenceTypeBoundingBox(presencetype, mins, maxs);
	VectorSubtract(absmins, maxs, newabsmins);
	VectorSubtract(absmaxs, mins, newabsmaxs);
	//relink the entity
	return AAS_AASLinkEntity(newabsmins, newabsmaxs, entnum);
}