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
struct secasvar {int flags; int /*<<< orphan*/  alg_auth; } ;
struct newah {int dummy; } ;
struct ah_algorithm {int (* sumsiz ) (struct secasvar*) ;} ;
struct ah {int dummy; } ;

/* Variables and functions */
 int SADB_X_EXT_OLD ; 
 struct ah_algorithm* ah_algorithm_lookup (int /*<<< orphan*/ ) ; 
 int stub1 (struct secasvar*) ; 
 int stub2 (struct secasvar*) ; 

int
ah_hdrlen(struct secasvar *sav)
{
	const struct ah_algorithm *algo;
	int plen, ahlen;
	
	algo = ah_algorithm_lookup(sav->alg_auth);
	if (!algo)
		return 0;
	if (sav->flags & SADB_X_EXT_OLD) {
		/* RFC 1826 */
		plen = ((*algo->sumsiz)(sav) + 3) & ~(4 - 1);	/*XXX pad to 8byte?*/
		ahlen = plen + sizeof(struct ah);
	} else {
		/* RFC 2402 */
		plen = ((*algo->sumsiz)(sav) + 3) & ~(4 - 1);	/*XXX pad to 8byte?*/
		ahlen = plen + sizeof(struct newah);
	}

	return(ahlen);
}