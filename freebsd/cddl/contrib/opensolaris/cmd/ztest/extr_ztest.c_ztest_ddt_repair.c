#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ zs_guid; } ;
typedef  TYPE_1__ ztest_shared_t ;
struct TYPE_17__ {scalar_t__ od_object; scalar_t__ od_blocksize; } ;
typedef  TYPE_2__ ztest_od_t ;
struct TYPE_18__ {int /*<<< orphan*/  zd_name; int /*<<< orphan*/ * zd_os; } ;
typedef  TYPE_3__ ztest_ds_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  od ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  enum zio_checksum { ____Placeholder_zio_checksum } zio_checksum ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_19__ {scalar_t__ dds_guid; } ;
typedef  TYPE_4__ dmu_objset_stats_t ;
struct TYPE_20__ {scalar_t__ db_offset; scalar_t__ db_size; int /*<<< orphan*/  db_data; } ;
typedef  TYPE_5__ dmu_buf_t ;
struct TYPE_21__ {int /*<<< orphan*/ * db_blkptr; } ;
typedef  TYPE_6__ dmu_buf_impl_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BP_GET_PSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DMU_OT_UINT64_OTHER ; 
 int /*<<< orphan*/  DMU_READ_NO_PREFETCH ; 
 int /*<<< orphan*/  FTAG ; 
 scalar_t__ MIN (scalar_t__,int) ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 int /*<<< orphan*/  VERIFY0 (int) ; 
 int /*<<< orphan*/  ZFS_PROP_COPIES ; 
 int /*<<< orphan*/  ZFS_PROP_DEDUP ; 
 int ZIO_DEDUPDITTO_MIN ; 
 int ZIO_FLAG_CANFAIL ; 
 int ZIO_FLAG_INDUCE_DAMAGE ; 
 int /*<<< orphan*/  ZIO_PRIORITY_SYNC_WRITE ; 
 int /*<<< orphan*/ * abd_alloc_linear (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abd_to_buf (int /*<<< orphan*/ *) ; 
 int dmu_buf_hold (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,TYPE_5__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_rele (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_will_fill (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_fast_stat (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  dmu_objset_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_tx_hold_write (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsl_pool_config_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_config_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,long long,long long,int) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int spa_dedup_checksum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_get_dsl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  zio_rewrite (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zio_wait (int /*<<< orphan*/ ) ; 
 scalar_t__ ztest_dsl_prop_set_uint64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ztest_name_lock ; 
 scalar_t__ ztest_object_init (TYPE_3__*,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ztest_od_init (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ztest_pattern_match (int /*<<< orphan*/ ,scalar_t__,unsigned long long) ; 
 int /*<<< orphan*/  ztest_pattern_set (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ ztest_random_blocksize () ; 
 TYPE_1__* ztest_shared ; 
 int /*<<< orphan*/ * ztest_spa ; 
 scalar_t__ ztest_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ztest_ddt_repair(ztest_ds_t *zd, uint64_t id)
{
	ztest_shared_t *zs = ztest_shared;
	spa_t *spa = ztest_spa;
	objset_t *os = zd->zd_os;
	ztest_od_t od[1];
	uint64_t object, blocksize, txg, pattern, psize;
	enum zio_checksum checksum = spa_dedup_checksum(spa);
	dmu_buf_t *db;
	dmu_tx_t *tx;
	abd_t *abd;
	blkptr_t blk;
	int copies = 2 * ZIO_DEDUPDITTO_MIN;

	blocksize = ztest_random_blocksize();
	blocksize = MIN(blocksize, 2048);	/* because we write so many */

	ztest_od_init(&od[0], id, FTAG, 0, DMU_OT_UINT64_OTHER, blocksize,
	    0, 0);

	if (ztest_object_init(zd, od, sizeof (od), B_FALSE) != 0)
		return;

	/*
	 * Take the name lock as writer to prevent anyone else from changing
	 * the pool and dataset properies we need to maintain during this test.
	 */
	rw_enter(&ztest_name_lock, RW_WRITER);

	if (ztest_dsl_prop_set_uint64(zd->zd_name, ZFS_PROP_DEDUP, checksum,
	    B_FALSE) != 0 ||
	    ztest_dsl_prop_set_uint64(zd->zd_name, ZFS_PROP_COPIES, 1,
	    B_FALSE) != 0) {
		rw_exit(&ztest_name_lock);
		return;
	}

	dmu_objset_stats_t dds;
	dsl_pool_config_enter(dmu_objset_pool(os), FTAG);
	dmu_objset_fast_stat(os, &dds);
	dsl_pool_config_exit(dmu_objset_pool(os), FTAG);

	object = od[0].od_object;
	blocksize = od[0].od_blocksize;
	pattern = zs->zs_guid ^ dds.dds_guid;

	ASSERT(object != 0);

	tx = dmu_tx_create(os);
	dmu_tx_hold_write(tx, object, 0, copies * blocksize);
	txg = ztest_tx_assign(tx, TXG_WAIT, FTAG);
	if (txg == 0) {
		rw_exit(&ztest_name_lock);
		return;
	}

	/*
	 * Write all the copies of our block.
	 */
	for (int i = 0; i < copies; i++) {
		uint64_t offset = i * blocksize;
		int error = dmu_buf_hold(os, object, offset, FTAG, &db,
		    DMU_READ_NO_PREFETCH);
		if (error != 0) {
			fatal(B_FALSE, "dmu_buf_hold(%p, %llu, %llu) = %u",
			    os, (long long)object, (long long) offset, error);
		}
		ASSERT(db->db_offset == offset);
		ASSERT(db->db_size == blocksize);
		ASSERT(ztest_pattern_match(db->db_data, db->db_size, pattern) ||
		    ztest_pattern_match(db->db_data, db->db_size, 0ULL));
		dmu_buf_will_fill(db, tx);
		ztest_pattern_set(db->db_data, db->db_size, pattern);
		dmu_buf_rele(db, FTAG);
	}

	dmu_tx_commit(tx);
	txg_wait_synced(spa_get_dsl(spa), txg);

	/*
	 * Find out what block we got.
	 */
	VERIFY0(dmu_buf_hold(os, object, 0, FTAG, &db,
	    DMU_READ_NO_PREFETCH));
	blk = *((dmu_buf_impl_t *)db)->db_blkptr;
	dmu_buf_rele(db, FTAG);

	/*
	 * Damage the block.  Dedup-ditto will save us when we read it later.
	 */
	psize = BP_GET_PSIZE(&blk);
	abd = abd_alloc_linear(psize, B_TRUE);
	ztest_pattern_set(abd_to_buf(abd), psize, ~pattern);

	(void) zio_wait(zio_rewrite(NULL, spa, 0, &blk,
	    abd, psize, NULL, NULL, ZIO_PRIORITY_SYNC_WRITE,
	    ZIO_FLAG_CANFAIL | ZIO_FLAG_INDUCE_DAMAGE, NULL));

	abd_free(abd);

	rw_exit(&ztest_name_lock);
}