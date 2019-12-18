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
typedef  int u_int ;
struct sroute {int /*<<< orphan*/ * index; } ;
struct asn_oid {int len; int /*<<< orphan*/ * subs; } ;

/* Variables and functions */
 struct sroute* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sroute*) ; 
 int /*<<< orphan*/  sroutes ; 

__attribute__((used)) static struct sroute *
sroute_get(const struct asn_oid *oid, u_int sub)
{
	struct sroute key;
	int i;

	if (oid->len - sub != 13)
		return (NULL);
	for (i = 0; i < 13; i++)
		key.index[i] = oid->subs[sub + i];
	return (RB_FIND(sroutes, &sroutes, &key));
}