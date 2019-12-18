#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int /*<<< orphan*/ * uio_t ;
typedef  int /*<<< orphan*/  uio_buf ;
typedef  int /*<<< orphan*/  uint8_t ;
struct dirent {scalar_t__ d_ino; int d_namlen; char* d_name; int d_reclen; } ;
typedef  scalar_t__ errno_t ;
struct TYPE_9__ {scalar_t__ v_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAST_USER_ADDR_T (char*) ; 
 scalar_t__ EBUSY ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ENOMEM ; 
 scalar_t__ ENOTEMPTY ; 
 int /*<<< orphan*/  FREAD ; 
 int /*<<< orphan*/  FREE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MALLOC (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int UIO_BUFF_SIZE ; 
 int /*<<< orphan*/  UIO_READ ; 
 int UIO_SIZEOF (int) ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int VNODE_REMOVE_NO_AUDIT_PATH ; 
 int VNODE_REMOVE_SKIP_NAMESPACE_EVENT ; 
 int /*<<< orphan*/  VNOP_CLOSE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VNOP_OPEN (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VNOP_READDIR (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ VT_HFS ; 
 scalar_t__ VT_NFS ; 
 int /*<<< orphan*/  caddr_t ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  uio_addiov (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * uio_createwithbuffer (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  uio_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uio_offset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uio_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ uio_resid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uio_setoffset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlink1 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vnode_resume (TYPE_1__*) ; 
 scalar_t__ vnode_suspend (TYPE_1__*) ; 

errno_t rmdir_remove_orphaned_appleDouble(vnode_t vp , vfs_context_t ctx, int * restart_flag) 
{

#define UIO_BUFF_SIZE 2048
	uio_t auio = NULL;
	int eofflag, siz = UIO_BUFF_SIZE, nentries = 0;
	int open_flag = 0, full_erase_flag = 0;
	char uio_buf[ UIO_SIZEOF(1) ];
	char *rbuf = NULL;
   	void *dir_pos;
	void *dir_end;
	struct dirent *dp;
	errno_t error;

	error = vnode_suspend(vp);

	/*
	 * restart_flag is set so that the calling rmdir sleeps and resets
	 */
	if (error == EBUSY)
		*restart_flag = 1;
	if (error != 0)
		return (error);

	/*
	 * set up UIO
	 */
	MALLOC(rbuf, caddr_t, siz, M_TEMP, M_WAITOK);
	if (rbuf)
		auio = uio_createwithbuffer(1, 0, UIO_SYSSPACE, UIO_READ,
				&uio_buf[0], sizeof(uio_buf));
	if (!rbuf || !auio) {
		error = ENOMEM;
		goto outsc;
	}

	uio_setoffset(auio,0);

	eofflag = 0;

	if ((error = VNOP_OPEN(vp, FREAD, ctx))) 
		goto outsc; 	
	else
		open_flag = 1;

	/*
	 * First pass checks if all files are appleDouble files.
	 */

	do {
		siz = UIO_BUFF_SIZE;
		uio_reset(auio, uio_offset(auio), UIO_SYSSPACE, UIO_READ);
		uio_addiov(auio, CAST_USER_ADDR_T(rbuf), UIO_BUFF_SIZE);

		if((error = VNOP_READDIR(vp, auio, 0, &eofflag, &nentries, ctx)))
			goto outsc;

		if (uio_resid(auio) != 0) 
			siz -= uio_resid(auio);

		/*
		 * Iterate through directory
		 */
		dir_pos = (void*) rbuf;
		dir_end = (void*) (rbuf + siz);
		dp = (struct dirent*) (dir_pos);

		if (dir_pos == dir_end)
			eofflag = 1;

		while (dir_pos < dir_end) {
			/*
			 * Check for . and .. as well as directories
			 */
			if (dp->d_ino != 0 && 
					!((dp->d_namlen == 1 && dp->d_name[0] == '.') ||
					    (dp->d_namlen == 2 && dp->d_name[0] == '.' && dp->d_name[1] == '.'))) {
				/*
				 * Check for irregular files and ._ files
				 * If there is a ._._ file abort the op
				 */
				if ( dp->d_namlen < 2 ||
						strncmp(dp->d_name,"._",2) ||
						(dp->d_namlen >= 4 && !strncmp(&(dp->d_name[2]), "._",2))) {
					error = ENOTEMPTY;
					goto outsc;
				}
			}
			dir_pos = (void*) ((uint8_t*)dir_pos + dp->d_reclen);
			dp = (struct dirent*)dir_pos;
		}
		
		/*
		 * workaround for HFS/NFS setting eofflag before end of file 
		 */
		if (vp->v_tag == VT_HFS && nentries > 2)
			eofflag=0;

		if (vp->v_tag == VT_NFS) {
			if (eofflag && !full_erase_flag) {
				full_erase_flag = 1;
				eofflag = 0;
				uio_reset(auio, 0, UIO_SYSSPACE, UIO_READ);
			}
			else if (!eofflag && full_erase_flag)
				full_erase_flag = 0;
		}

	} while (!eofflag);
	/*
	 * If we've made it here all the files in the dir are ._ files.
	 * We can delete the files even though the node is suspended
	 * because we are the owner of the file.
	 */

	uio_reset(auio, 0, UIO_SYSSPACE, UIO_READ);
	eofflag = 0;
	full_erase_flag = 0;

	do {
		siz = UIO_BUFF_SIZE;
		uio_reset(auio, uio_offset(auio), UIO_SYSSPACE, UIO_READ);
		uio_addiov(auio, CAST_USER_ADDR_T(rbuf), UIO_BUFF_SIZE);

		error = VNOP_READDIR(vp, auio, 0, &eofflag, &nentries, ctx);

		if (error != 0) 
			goto outsc;

		if (uio_resid(auio) != 0) 
			siz -= uio_resid(auio);

		/*
		 * Iterate through directory
		 */
		dir_pos = (void*) rbuf;
		dir_end = (void*) (rbuf + siz);
		dp = (struct dirent*) dir_pos;
		
		if (dir_pos == dir_end)
			eofflag = 1;
	
		while (dir_pos < dir_end) {
			/*
			 * Check for . and .. as well as directories
			 */
			if (dp->d_ino != 0 && 
					!((dp->d_namlen == 1 && dp->d_name[0] == '.') ||
					    (dp->d_namlen == 2 && dp->d_name[0] == '.' && dp->d_name[1] == '.'))
					  ) {
	
				error = unlink1(ctx, vp,
				    CAST_USER_ADDR_T(dp->d_name), UIO_SYSSPACE,
				    VNODE_REMOVE_SKIP_NAMESPACE_EVENT |
				    VNODE_REMOVE_NO_AUDIT_PATH);

				if (error &&  error != ENOENT) {
					goto outsc;
				}

			}
			dir_pos = (void*) ((uint8_t*)dir_pos + dp->d_reclen);
			dp = (struct dirent*)dir_pos;
		}
		
		/*
		 * workaround for HFS/NFS setting eofflag before end of file 
		 */
		if (vp->v_tag == VT_HFS && nentries > 2)
			eofflag=0;

		if (vp->v_tag == VT_NFS) {
			if (eofflag && !full_erase_flag) {
				full_erase_flag = 1;
				eofflag = 0;
				uio_reset(auio, 0, UIO_SYSSPACE, UIO_READ);
			}
			else if (!eofflag && full_erase_flag)
				full_erase_flag = 0;
		}

	} while (!eofflag);


	error = 0;

outsc:
	if (open_flag)
		VNOP_CLOSE(vp, FREAD, ctx);

	if (auio)
		uio_free(auio);
	FREE(rbuf, M_TEMP);

	vnode_resume(vp);


	return(error);

}