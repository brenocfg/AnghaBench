#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int page_len; int /*<<< orphan*/ * pages; struct kvec* head; } ;
struct svc_rqst {TYPE_1__ rq_arg; int /*<<< orphan*/  rq_resused; int /*<<< orphan*/ * rq_respages; } ;
struct nfsd3_symlinkargs {char* tname; unsigned int tlen; int /*<<< orphan*/  attrs; int /*<<< orphan*/  flen; int /*<<< orphan*/  fname; int /*<<< orphan*/  ffh; } ;
struct kvec {int iov_len; scalar_t__ iov_base; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 unsigned int NFS3_MAXPATHLEN ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/ * decode_fh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * decode_filename (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * decode_sattr3 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int ntohl (int /*<<< orphan*/ ) ; 
 char* page_address (int /*<<< orphan*/ ) ; 

int
nfs3svc_decode_symlinkargs(struct svc_rqst *rqstp, __be32 *p,
					struct nfsd3_symlinkargs *args)
{
	unsigned int len, avail;
	char *old, *new;
	struct kvec *vec;

	if (!(p = decode_fh(p, &args->ffh)) ||
	    !(p = decode_filename(p, &args->fname, &args->flen))
		)
		return 0;
	p = decode_sattr3(p, &args->attrs);

	/* now decode the pathname, which might be larger than the first page.
	 * As we have to check for nul's anyway, we copy it into a new page
	 * This page appears in the rq_res.pages list, but as pages_len is always
	 * 0, it won't get in the way
	 */
	len = ntohl(*p++);
	if (len == 0 || len > NFS3_MAXPATHLEN || len >= PAGE_SIZE)
		return 0;
	args->tname = new =
		page_address(rqstp->rq_respages[rqstp->rq_resused++]);
	args->tlen = len;
	/* first copy and check from the first page */
	old = (char*)p;
	vec = &rqstp->rq_arg.head[0];
	avail = vec->iov_len - (old - (char*)vec->iov_base);
	while (len && avail && *old) {
		*new++ = *old++;
		len--;
		avail--;
	}
	/* now copy next page if there is one */
	if (len && !avail && rqstp->rq_arg.page_len) {
		avail = rqstp->rq_arg.page_len;
		if (avail > PAGE_SIZE)
			avail = PAGE_SIZE;
		old = page_address(rqstp->rq_arg.pages[0]);
	}
	while (len && avail && *old) {
		*new++ = *old++;
		len--;
		avail--;
	}
	*new = '\0';
	if (len)
		return 0;

	return 1;
}