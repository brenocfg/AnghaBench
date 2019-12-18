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
struct metapage {scalar_t__ data; } ;
struct inode {int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_sb; } ;
struct dbmap_disk {int /*<<< orphan*/  dn_maxfreebud; void* dn_agsize; void** dn_agfree; void* dn_agl2size; void* dn_agstart; void* dn_agwidth; void* dn_agheigth; void* dn_aglevel; void* dn_agpref; void* dn_maxag; void* dn_maxlevel; void* dn_numag; void* dn_l2nbperpage; void* dn_nfree; void* dn_mapsize; } ;
struct bmap {int /*<<< orphan*/  db_maxfreebud; int /*<<< orphan*/  db_agsize; int /*<<< orphan*/ * db_agfree; int /*<<< orphan*/  db_agl2size; int /*<<< orphan*/  db_agstart; int /*<<< orphan*/  db_agwidth; int /*<<< orphan*/  db_agheigth; int /*<<< orphan*/  db_aglevel; int /*<<< orphan*/  db_agpref; int /*<<< orphan*/  db_maxag; int /*<<< orphan*/  db_maxlevel; int /*<<< orphan*/  db_numag; int /*<<< orphan*/  db_l2nbperpage; int /*<<< orphan*/  db_nfree; int /*<<< orphan*/  db_mapsize; } ;
struct TYPE_2__ {int l2nbperpage; struct bmap* bmap; } ;

/* Variables and functions */
 int BMAPBLKNO ; 
 int EIO ; 
 TYPE_1__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int MAXAG ; 
 int /*<<< orphan*/  PSIZE ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diWriteSpecial (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jfs_err (char*) ; 
 struct metapage* read_metapage (struct inode*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_metapage (struct metapage*) ; 

int dbSync(struct inode *ipbmap)
{
	struct dbmap_disk *dbmp_le;
	struct bmap *bmp = JFS_SBI(ipbmap->i_sb)->bmap;
	struct metapage *mp;
	int i;

	/*
	 * write bmap global control page
	 */
	/* get the buffer for the on-disk bmap descriptor. */
	mp = read_metapage(ipbmap,
			   BMAPBLKNO << JFS_SBI(ipbmap->i_sb)->l2nbperpage,
			   PSIZE, 0);
	if (mp == NULL) {
		jfs_err("dbSync: read_metapage failed!");
		return -EIO;
	}
	/* copy the in-memory version of the bmap to the on-disk version */
	dbmp_le = (struct dbmap_disk *) mp->data;
	dbmp_le->dn_mapsize = cpu_to_le64(bmp->db_mapsize);
	dbmp_le->dn_nfree = cpu_to_le64(bmp->db_nfree);
	dbmp_le->dn_l2nbperpage = cpu_to_le32(bmp->db_l2nbperpage);
	dbmp_le->dn_numag = cpu_to_le32(bmp->db_numag);
	dbmp_le->dn_maxlevel = cpu_to_le32(bmp->db_maxlevel);
	dbmp_le->dn_maxag = cpu_to_le32(bmp->db_maxag);
	dbmp_le->dn_agpref = cpu_to_le32(bmp->db_agpref);
	dbmp_le->dn_aglevel = cpu_to_le32(bmp->db_aglevel);
	dbmp_le->dn_agheigth = cpu_to_le32(bmp->db_agheigth);
	dbmp_le->dn_agwidth = cpu_to_le32(bmp->db_agwidth);
	dbmp_le->dn_agstart = cpu_to_le32(bmp->db_agstart);
	dbmp_le->dn_agl2size = cpu_to_le32(bmp->db_agl2size);
	for (i = 0; i < MAXAG; i++)
		dbmp_le->dn_agfree[i] = cpu_to_le64(bmp->db_agfree[i]);
	dbmp_le->dn_agsize = cpu_to_le64(bmp->db_agsize);
	dbmp_le->dn_maxfreebud = bmp->db_maxfreebud;

	/* write the buffer */
	write_metapage(mp);

	/*
	 * write out dirty pages of bmap
	 */
	filemap_write_and_wait(ipbmap->i_mapping);

	diWriteSpecial(ipbmap, 0);

	return (0);
}