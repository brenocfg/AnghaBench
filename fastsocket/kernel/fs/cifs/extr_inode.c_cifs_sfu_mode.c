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
struct tcon_link {int dummy; } ;
struct cifs_tcon {int dummy; } ;
struct cifs_sb_info {int mnt_cifs_flags; int /*<<< orphan*/  local_nls; } ;
struct cifs_fattr {int cf_mode; } ;
typedef  int ssize_t ;
typedef  int __u32 ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int CIFSSMBQAllEAs (int,struct cifs_tcon*,unsigned char const*,char*,char*,int,int /*<<< orphan*/ ,int) ; 
 int CIFS_MOUNT_MAP_SPECIAL_CHR ; 
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct tcon_link*) ; 
 int PTR_ERR (struct tcon_link*) ; 
 int SFBITS_MASK ; 
 int /*<<< orphan*/  cFYI (int,char*,int,...) ; 
 int /*<<< orphan*/  cifs_put_tlink (struct tcon_link*) ; 
 struct tcon_link* cifs_sb_tlink (struct cifs_sb_info*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 struct cifs_tcon* tlink_tcon (struct tcon_link*) ; 

__attribute__((used)) static int cifs_sfu_mode(struct cifs_fattr *fattr, const unsigned char *path,
			 struct cifs_sb_info *cifs_sb, int xid)
{
#ifdef CONFIG_CIFS_XATTR
	ssize_t rc;
	char ea_value[4];
	__u32 mode;
	struct tcon_link *tlink;
	struct cifs_tcon *tcon;

	tlink = cifs_sb_tlink(cifs_sb);
	if (IS_ERR(tlink))
		return PTR_ERR(tlink);
	tcon = tlink_tcon(tlink);

	rc = CIFSSMBQAllEAs(xid, tcon, path, "SETFILEBITS",
			    ea_value, 4 /* size of buf */, cifs_sb->local_nls,
			    cifs_sb->mnt_cifs_flags &
				CIFS_MOUNT_MAP_SPECIAL_CHR);
	cifs_put_tlink(tlink);
	if (rc < 0)
		return (int)rc;
	else if (rc > 3) {
		mode = le32_to_cpu(*((__le32 *)ea_value));
		fattr->cf_mode &= ~SFBITS_MASK;
		cFYI(1, "special bits 0%o org mode 0%o", mode,
			 fattr->cf_mode);
		fattr->cf_mode = (mode & SFBITS_MASK) | fattr->cf_mode;
		cFYI(1, "special mode bits 0%o", mode);
	}

	return 0;
#else
	return -EOPNOTSUPP;
#endif
}