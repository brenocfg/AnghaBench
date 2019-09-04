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
typedef  scalar_t__ (* cmpfun ) (unsigned char*,unsigned char*) ;

/* Variables and functions */
 int /*<<< orphan*/  cycle (size_t,unsigned char**,int) ; 
 int pntz (size_t*) ; 
 int /*<<< orphan*/  shr (size_t*,int) ; 
 int /*<<< orphan*/  sift (unsigned char*,size_t,scalar_t__ (*) (unsigned char*,unsigned char*),int,size_t*) ; 
 scalar_t__ stub1 (unsigned char*,unsigned char*) ; 
 scalar_t__ stub2 (unsigned char*,unsigned char*) ; 
 scalar_t__ stub3 (unsigned char*,unsigned char*) ; 

__attribute__((used)) static void trinkle(unsigned char *head, size_t width, cmpfun cmp, size_t pp[2], int pshift, int trusty, size_t lp[])
{
	unsigned char *stepson,
	              *rt, *lf;
	size_t p[2];
	unsigned char *ar[14 * sizeof(size_t) + 1];
	int i = 1;
	int trail;

	p[0] = pp[0];
	p[1] = pp[1];

	ar[0] = head;
	while(p[0] != 1 || p[1] != 0) {
		stepson = head - lp[pshift];
		if((*cmp)(stepson, ar[0]) <= 0) {
			break;
		}
		if(!trusty && pshift > 1) {
			rt = head - width;
			lf = head - width - lp[pshift - 2];
			if((*cmp)(rt, stepson) >= 0 || (*cmp)(lf, stepson) >= 0) {
				break;
			}
		}

		ar[i++] = stepson;
		head = stepson;
		trail = pntz(p);
		shr(p, trail);
		pshift += trail;
		trusty = 0;
	}
	if(!trusty) {
		cycle(width, ar, i);
		sift(head, width, cmp, pshift, lp);
	}
}