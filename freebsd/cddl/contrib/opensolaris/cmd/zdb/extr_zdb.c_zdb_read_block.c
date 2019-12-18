#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
struct TYPE_28__ {char* vdev_path; struct TYPE_28__* vdev_top; int /*<<< orphan*/  vdev_id; TYPE_1__* vdev_ops; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  size_t uchar_t ;
struct TYPE_29__ {int /*<<< orphan*/  spa_root_vdev; } ;
typedef  TYPE_3__ spa_t ;
typedef  enum zio_compress { ____Placeholder_zio_compress } zio_compress ;
typedef  int /*<<< orphan*/  dva_t ;
struct TYPE_30__ {int /*<<< orphan*/ * blk_dva; } ;
typedef  TYPE_4__ blkptr_t ;
typedef  int /*<<< orphan*/  abd_t ;
struct TYPE_27__ {char* vdev_op_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BP_SET_BIRTH (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_BYTEORDER (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_CHECKSUM (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_COMPRESS (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_DEDUP (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_LEVEL (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_SET_LSIZE (TYPE_4__*,int) ; 
 int /*<<< orphan*/  BP_SET_PSIZE (TYPE_4__*,int) ; 
 int /*<<< orphan*/  BP_SET_TYPE (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BP_ZERO (TYPE_4__*) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  DEV_BSIZE ; 
 int /*<<< orphan*/  DMU_OT_NONE ; 
 int /*<<< orphan*/  DVA_SET_ASIZE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DVA_SET_GANG (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DVA_SET_OFFSET (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DVA_SET_VDEV (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  IS_P2ALIGNED (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  SCL_STATE ; 
 int SPA_MAXBLOCKSIZE ; 
 scalar_t__ SPA_MINBLOCKSIZE ; 
 int /*<<< orphan*/  TXG_INITIAL ; 
 int /*<<< orphan*/  UMEM_NOFAIL ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int ZDB_FLAG_CHECKSUM ; 
 int ZDB_FLAG_DECOMPRESS ; 
 int ZDB_FLAG_GBH ; 
 int ZDB_FLAG_INDIRECT ; 
 int ZDB_FLAG_PRINT_BLKPTR ; 
 int ZDB_FLAG_RAW ; 
 int /*<<< orphan*/  ZFS_HOST_BYTEORDER ; 
 int /*<<< orphan*/  ZIO_CHECKSUM_OFF ; 
 int ZIO_COMPRESS_FUNCTIONS ; 
 int /*<<< orphan*/  ZIO_COMPRESS_OFF ; 
 int ZIO_FLAG_CANFAIL ; 
 int ZIO_FLAG_DONT_CACHE ; 
 int ZIO_FLAG_DONT_PROPAGATE ; 
 int ZIO_FLAG_DONT_QUEUE ; 
 int ZIO_FLAG_DONT_RETRY ; 
 int ZIO_FLAG_OPTIONAL ; 
 int ZIO_FLAG_RAW ; 
 int /*<<< orphan*/  ZIO_PRIORITY_SYNC_READ ; 
 int /*<<< orphan*/  ZIO_TYPE_READ ; 
 int /*<<< orphan*/ * abd_alloc_linear (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_copy_to_buf (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  abd_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  abd_iterate_func (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* abd_to_buf (int /*<<< orphan*/ *) ; 
 scalar_t__ bcmp (void*,void*,int) ; 
 int* flagbits ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  random_get_pseudo_bytes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  random_get_pseudo_bytes_cb ; 
 int /*<<< orphan*/  spa_config_enter (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_config_exit (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (char const*) ; 
 char* strtok (char*,char*) ; 
 int strtoull (char const*,char**,int) ; 
 void* umem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umem_free (void*,int) ; 
 int /*<<< orphan*/  vdev_psize_to_asize (TYPE_2__*,int) ; 
 int /*<<< orphan*/  zdb_dump_block (char*,void*,int,int) ; 
 int /*<<< orphan*/  zdb_dump_block_raw (void*,int,int) ; 
 int /*<<< orphan*/  zdb_dump_gbh (void*,int) ; 
 int /*<<< orphan*/  zdb_dump_indirect (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  zdb_print_blkptr (TYPE_4__*,int) ; 
 TYPE_2__* zdb_vdev_lookup (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ zio_decompress_data (int,int /*<<< orphan*/ *,void*,int,int) ; 
 scalar_t__ zio_decompress_data_buf (int,void*,void*,int,int) ; 
 int /*<<< orphan*/  zio_nowait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_read (int /*<<< orphan*/ *,TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zio_root (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_vdev_child_io (int /*<<< orphan*/ *,TYPE_4__*,TYPE_2__*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zio_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zdb_read_block(char *thing, spa_t *spa)
{
	blkptr_t blk, *bp = &blk;
	dva_t *dva = bp->blk_dva;
	int flags = 0;
	uint64_t offset = 0, size = 0, psize = 0, lsize = 0, blkptr_offset = 0;
	zio_t *zio;
	vdev_t *vd;
	abd_t *pabd;
	void *lbuf, *buf;
	const char *s, *vdev;
	char *p, *dup, *flagstr;
	int i, error;

	dup = strdup(thing);
	s = strtok(dup, ":");
	vdev = s ? s : "";
	s = strtok(NULL, ":");
	offset = strtoull(s ? s : "", NULL, 16);
	s = strtok(NULL, ":");
	size = strtoull(s ? s : "", NULL, 16);
	s = strtok(NULL, ":");
	if (s)
		flagstr = strdup(s);
	else
		flagstr = strdup("");

	s = NULL;
	if (size == 0)
		s = "size must not be zero";
	if (!IS_P2ALIGNED(size, DEV_BSIZE))
		s = "size must be a multiple of sector size";
	if (!IS_P2ALIGNED(offset, DEV_BSIZE))
		s = "offset must be a multiple of sector size";
	if (s) {
		(void) printf("Invalid block specifier: %s  - %s\n", thing, s);
		free(flagstr);
		free(dup);
		return;
	}

	for (s = strtok(flagstr, ":"); s; s = strtok(NULL, ":")) {
		for (i = 0; flagstr[i]; i++) {
			int bit = flagbits[(uchar_t)flagstr[i]];

			if (bit == 0) {
				(void) printf("***Invalid flag: %c\n",
				    flagstr[i]);
				continue;
			}
			flags |= bit;

			/* If it's not something with an argument, keep going */
			if ((bit & (ZDB_FLAG_CHECKSUM |
			    ZDB_FLAG_PRINT_BLKPTR)) == 0)
				continue;

			p = &flagstr[i + 1];
			if (bit == ZDB_FLAG_PRINT_BLKPTR)
				blkptr_offset = strtoull(p, &p, 16);
			if (*p != ':' && *p != '\0') {
				(void) printf("***Invalid flag arg: '%s'\n", s);
				free(flagstr);
				free(dup);
				return;
			}
			i += p - &flagstr[i + 1]; /* skip over the number */
		}
	}
	free(flagstr);

	vd = zdb_vdev_lookup(spa->spa_root_vdev, vdev);
	if (vd == NULL) {
		(void) printf("***Invalid vdev: %s\n", vdev);
		free(dup);
		return;
	} else {
		if (vd->vdev_path)
			(void) fprintf(stderr, "Found vdev: %s\n",
			    vd->vdev_path);
		else
			(void) fprintf(stderr, "Found vdev type: %s\n",
			    vd->vdev_ops->vdev_op_type);
	}

	psize = size;
	lsize = size;

	pabd = abd_alloc_linear(SPA_MAXBLOCKSIZE, B_FALSE);
	lbuf = umem_alloc(SPA_MAXBLOCKSIZE, UMEM_NOFAIL);

	BP_ZERO(bp);

	DVA_SET_VDEV(&dva[0], vd->vdev_id);
	DVA_SET_OFFSET(&dva[0], offset);
	DVA_SET_GANG(&dva[0], !!(flags & ZDB_FLAG_GBH));
	DVA_SET_ASIZE(&dva[0], vdev_psize_to_asize(vd, psize));

	BP_SET_BIRTH(bp, TXG_INITIAL, TXG_INITIAL);

	BP_SET_LSIZE(bp, lsize);
	BP_SET_PSIZE(bp, psize);
	BP_SET_COMPRESS(bp, ZIO_COMPRESS_OFF);
	BP_SET_CHECKSUM(bp, ZIO_CHECKSUM_OFF);
	BP_SET_TYPE(bp, DMU_OT_NONE);
	BP_SET_LEVEL(bp, 0);
	BP_SET_DEDUP(bp, 0);
	BP_SET_BYTEORDER(bp, ZFS_HOST_BYTEORDER);

	spa_config_enter(spa, SCL_STATE, FTAG, RW_READER);
	zio = zio_root(spa, NULL, NULL, 0);

	if (vd == vd->vdev_top) {
		/*
		 * Treat this as a normal block read.
		 */
		zio_nowait(zio_read(zio, spa, bp, pabd, psize, NULL, NULL,
		    ZIO_PRIORITY_SYNC_READ,
		    ZIO_FLAG_CANFAIL | ZIO_FLAG_RAW, NULL));
	} else {
		/*
		 * Treat this as a vdev child I/O.
		 */
		zio_nowait(zio_vdev_child_io(zio, bp, vd, offset, pabd,
		    psize, ZIO_TYPE_READ, ZIO_PRIORITY_SYNC_READ,
		    ZIO_FLAG_DONT_CACHE | ZIO_FLAG_DONT_QUEUE |
		    ZIO_FLAG_DONT_PROPAGATE | ZIO_FLAG_DONT_RETRY |
		    ZIO_FLAG_CANFAIL | ZIO_FLAG_RAW | ZIO_FLAG_OPTIONAL,
		    NULL, NULL));
	}

	error = zio_wait(zio);
	spa_config_exit(spa, SCL_STATE, FTAG);

	if (error) {
		(void) printf("Read of %s failed, error: %d\n", thing, error);
		goto out;
	}

	if (flags & ZDB_FLAG_DECOMPRESS) {
		/*
		 * We don't know how the data was compressed, so just try
		 * every decompress function at every inflated blocksize.
		 */
		enum zio_compress c;
		void *pbuf2 = umem_alloc(SPA_MAXBLOCKSIZE, UMEM_NOFAIL);
		void *lbuf2 = umem_alloc(SPA_MAXBLOCKSIZE, UMEM_NOFAIL);

		abd_copy_to_buf(pbuf2, pabd, psize);

		VERIFY0(abd_iterate_func(pabd, psize, SPA_MAXBLOCKSIZE - psize,
		    random_get_pseudo_bytes_cb, NULL));

		VERIFY0(random_get_pseudo_bytes((uint8_t *)pbuf2 + psize,
		    SPA_MAXBLOCKSIZE - psize));

		for (lsize = SPA_MAXBLOCKSIZE; lsize > psize;
		    lsize -= SPA_MINBLOCKSIZE) {
			for (c = 0; c < ZIO_COMPRESS_FUNCTIONS; c++) {
				if (zio_decompress_data(c, pabd,
				    lbuf, psize, lsize) == 0 &&
				    zio_decompress_data_buf(c, pbuf2,
				    lbuf2, psize, lsize) == 0 &&
				    bcmp(lbuf, lbuf2, lsize) == 0)
					break;
			}
			if (c != ZIO_COMPRESS_FUNCTIONS)
				break;
			lsize -= SPA_MINBLOCKSIZE;
		}

		umem_free(pbuf2, SPA_MAXBLOCKSIZE);
		umem_free(lbuf2, SPA_MAXBLOCKSIZE);

		if (lsize <= psize) {
			(void) printf("Decompress of %s failed\n", thing);
			goto out;
		}
		buf = lbuf;
		size = lsize;
	} else {
		buf = abd_to_buf(pabd);
		size = psize;
	}

	if (flags & ZDB_FLAG_PRINT_BLKPTR)
		zdb_print_blkptr((blkptr_t *)(void *)
		    ((uintptr_t)buf + (uintptr_t)blkptr_offset), flags);
	else if (flags & ZDB_FLAG_RAW)
		zdb_dump_block_raw(buf, size, flags);
	else if (flags & ZDB_FLAG_INDIRECT)
		zdb_dump_indirect((blkptr_t *)buf, size / sizeof (blkptr_t),
		    flags);
	else if (flags & ZDB_FLAG_GBH)
		zdb_dump_gbh(buf, flags);
	else
		zdb_dump_block(thing, buf, size, flags);

out:
	abd_free(pabd);
	umem_free(lbuf, SPA_MAXBLOCKSIZE);
	free(dup);
}