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
struct isdn_ppp_comp_data {int optlen; scalar_t__ num; int flags; int /*<<< orphan*/ * options; } ;
struct bsd_dict {int dummy; } ;
struct bsd_db {int xmit; int totlen; unsigned int hsize; unsigned int hshift; unsigned int maxmaxcode; int maxbits; int /*<<< orphan*/ * lens; void* dict; } ;

/* Variables and functions */
 scalar_t__ BSD_CURRENT_VERSION ; 
 int BSD_NBITS (int /*<<< orphan*/ ) ; 
 scalar_t__ BSD_VERSION (int /*<<< orphan*/ ) ; 
 scalar_t__ CI_BSD_COMPRESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IPPP_COMP_FLAG_XMIT ; 
 unsigned int MAXCODE (int) ; 
 int /*<<< orphan*/  bsd_free (struct bsd_db*) ; 
 struct bsd_db* kzalloc (int,int /*<<< orphan*/ ) ; 
 void* vmalloc (unsigned int) ; 

__attribute__((used)) static void *bsd_alloc (struct isdn_ppp_comp_data *data)
{
	int bits;
	unsigned int hsize, hshift, maxmaxcode;
	struct bsd_db *db;
	int decomp;

	static unsigned int htab[][2] = {
		{ 5003 , 4 } , { 5003 , 4 } , { 5003 , 4 } , { 5003 , 4 } , 
		{ 9001 , 5 } , { 18013 , 6 } , { 35023 , 7 } , { 69001 , 8 } 
	};
		
	if (data->optlen != 1 || data->num != CI_BSD_COMPRESS
		|| BSD_VERSION(data->options[0]) != BSD_CURRENT_VERSION)
		return NULL;

	bits = BSD_NBITS(data->options[0]);

	if(bits < 9 || bits > 15)
		return NULL;

	hsize = htab[bits-9][0];
	hshift = htab[bits-9][1];
	
	/*
	 * Allocate the main control structure for this instance.
	 */
	maxmaxcode = MAXCODE(bits);
	db = kzalloc (sizeof (struct bsd_db),GFP_KERNEL);
	if (!db)
		return NULL;

	db->xmit = data->flags & IPPP_COMP_FLAG_XMIT;
	decomp = db->xmit ? 0 : 1;

	/*
	 * Allocate space for the dictionary. This may be more than one page in
	 * length.
	 */
	db->dict = vmalloc(hsize * sizeof(struct bsd_dict));
	if (!db->dict) {
		bsd_free (db);
		return NULL;
	}

	/*
	 * If this is the compression buffer then there is no length data.
	 * For decompression, the length information is needed as well.
	 */
	if (!decomp)
		db->lens = NULL;
	else {
		db->lens = vmalloc((maxmaxcode + 1) * sizeof(db->lens[0]));
		if (!db->lens) {
			bsd_free (db);
			return (NULL);
		}
	}

	/*
	 * Initialize the data information for the compression code
	 */
	db->totlen     = sizeof (struct bsd_db) + (sizeof (struct bsd_dict) * hsize);
	db->hsize      = hsize;
	db->hshift     = hshift;
	db->maxmaxcode = maxmaxcode;
	db->maxbits    = bits;

	return (void *) db;
}