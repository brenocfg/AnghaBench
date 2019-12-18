#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  zl_spa; int /*<<< orphan*/  zl_os; TYPE_2__* zl_header; } ;
typedef  TYPE_3__ zilog_t ;
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_12__ {int lrc_reclen; } ;
struct TYPE_16__ {scalar_t__ blk_birth; } ;
struct TYPE_15__ {int lr_offset; int lr_length; scalar_t__ lr_foid; TYPE_1__ lr_common; TYPE_5__ lr_blkptr; } ;
typedef  TYPE_4__ lr_write_t ;
typedef  TYPE_5__ blkptr_t ;
typedef  int /*<<< orphan*/  abd_t ;
struct TYPE_13__ {scalar_t__ zh_claim_txg; } ;

/* Variables and functions */
 int BP_GET_LSIZE (TYPE_5__*) ; 
 scalar_t__ BP_IS_HOLE (TYPE_5__*) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIN (int,int) ; 
 int /*<<< orphan*/  SET_BOOKMARK (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int SPA_MAXBLOCKSIZE ; 
 int TX_WRITE2 ; 
 int /*<<< orphan*/  ZB_ZIL_LEVEL ; 
 int /*<<< orphan*/  ZIO_FLAG_CANFAIL ; 
 int /*<<< orphan*/  ZIO_PRIORITY_SYNC_READ ; 
 int /*<<< orphan*/ * abd_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_copy_from_buf (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  abd_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abd_iterate_func (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dump_opt ; 
 int /*<<< orphan*/  print_log_bp (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ spa_min_claim_txg (int /*<<< orphan*/ ) ; 
 char* tab_prefix ; 
 int /*<<< orphan*/  zil_prt_rec_write_cb ; 
 int /*<<< orphan*/  zio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int zio_wait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zil_prt_rec_write(zilog_t *zilog, int txtype, void *arg)
{
	lr_write_t *lr = arg;
	abd_t *data;
	blkptr_t *bp = &lr->lr_blkptr;
	zbookmark_phys_t zb;
	int verbose = MAX(dump_opt['d'], dump_opt['i']);
	int error;

	(void) printf("%sfoid %llu, offset %llx, length %llx\n", tab_prefix,
	    (u_longlong_t)lr->lr_foid, (u_longlong_t)lr->lr_offset,
	    (u_longlong_t)lr->lr_length);

	if (txtype == TX_WRITE2 || verbose < 5)
		return;

	if (lr->lr_common.lrc_reclen == sizeof (lr_write_t)) {
		(void) printf("%shas blkptr, %s\n", tab_prefix,
		    !BP_IS_HOLE(bp) &&
		    bp->blk_birth >= spa_min_claim_txg(zilog->zl_spa) ?
		    "will claim" : "won't claim");
		print_log_bp(bp, tab_prefix);

		if (BP_IS_HOLE(bp)) {
			(void) printf("\t\t\tLSIZE 0x%llx\n",
			    (u_longlong_t)BP_GET_LSIZE(bp));
			(void) printf("%s<hole>\n", tab_prefix);
			return;
		}
		if (bp->blk_birth < zilog->zl_header->zh_claim_txg) {
			(void) printf("%s<block already committed>\n",
			    tab_prefix);
			return;
		}

		SET_BOOKMARK(&zb, dmu_objset_id(zilog->zl_os),
		    lr->lr_foid, ZB_ZIL_LEVEL,
		    lr->lr_offset / BP_GET_LSIZE(bp));

		data = abd_alloc(BP_GET_LSIZE(bp), B_FALSE);
		error = zio_wait(zio_read(NULL, zilog->zl_spa,
		    bp, data, BP_GET_LSIZE(bp), NULL, NULL,
		    ZIO_PRIORITY_SYNC_READ, ZIO_FLAG_CANFAIL, &zb));
		if (error)
			goto out;
	} else {
		/* data is stored after the end of the lr_write record */
		data = abd_alloc(lr->lr_length, B_FALSE);
		abd_copy_from_buf(data, lr + 1, lr->lr_length);
	}

	(void) printf("%s", tab_prefix);
	(void) abd_iterate_func(data,
	    0, MIN(lr->lr_length, (verbose < 6 ? 20 : SPA_MAXBLOCKSIZE)),
	    zil_prt_rec_write_cb, NULL);
	(void) printf("\n");

out:
	abd_free(data);
}