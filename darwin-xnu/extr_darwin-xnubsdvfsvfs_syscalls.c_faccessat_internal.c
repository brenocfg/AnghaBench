#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vfs_context_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
struct vfs_context {int /*<<< orphan*/  vc_ucred; int /*<<< orphan*/  vc_thread; } ;
struct nameidata {int /*<<< orphan*/  ni_dvp; int /*<<< orphan*/  ni_vp; } ;
typedef  enum uio_seg { ____Placeholder_uio_seg } uio_seg ;
struct TYPE_3__ {int /*<<< orphan*/  vc_thread; int /*<<< orphan*/  vc_ucred; } ;

/* Variables and functions */
 int AT_EACCESS ; 
 int AUDITVNPATH1 ; 
 int FOLLOW ; 
 int /*<<< orphan*/  LOOKUP ; 
 int /*<<< orphan*/  NDINIT (struct nameidata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,struct vfs_context*) ; 
 int /*<<< orphan*/  OP_ACCESS ; 
 int WANTPARENT ; 
 int _DELETE_OK ; 
 int access1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct vfs_context*) ; 
 int /*<<< orphan*/  kauth_cred_copy_real (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int /*<<< orphan*/  kauth_cred_unref (int /*<<< orphan*/ *) ; 
 int nameiat (struct nameidata*,int) ; 
 int /*<<< orphan*/  nameidone (struct nameidata*) ; 
 int /*<<< orphan*/  vnode_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
faccessat_internal(vfs_context_t ctx, int fd, user_addr_t path, int amode,
    int flag, enum uio_seg segflg)
{
	int error;
	struct nameidata nd;
 	int niopts;
	struct vfs_context context;
#if NAMEDRSRCFORK
	int is_namedstream = 0;
#endif

 	/*
	 * Unless the AT_EACCESS option is used, Access is defined as checking
	 * against the process' real identity, even if operations are checking
	 * the effective identity.  So we need to tweak the credential
 	 * in the context for that case.
 	 */
	if (!(flag & AT_EACCESS))
		context.vc_ucred = kauth_cred_copy_real(kauth_cred_get());
	else
		context.vc_ucred = ctx->vc_ucred;
	context.vc_thread = ctx->vc_thread;


	niopts = FOLLOW | AUDITVNPATH1;
 	/* need parent for vnode_authorize for deletion test */
 	if (amode & _DELETE_OK)
 		niopts |= WANTPARENT;
 	NDINIT(&nd, LOOKUP, OP_ACCESS, niopts, segflg,
	       path, &context);

#if NAMEDRSRCFORK
	/* access(F_OK) calls are allowed for resource forks. */
	if (amode == F_OK)
		nd.ni_cnd.cn_flags |= CN_ALLOWRSRCFORK;
#endif
 	error = nameiat(&nd, fd);
 	if (error)
 		goto out;

#if NAMEDRSRCFORK
	/* Grab reference on the shadow stream file vnode to
	 * force an inactive on release which will mark it
	 * for recycle.
	 */
	if (vnode_isnamedstream(nd.ni_vp) &&
	    (nd.ni_vp->v_parent != NULLVP) &&
	    vnode_isshadow(nd.ni_vp)) {
		is_namedstream = 1;
		vnode_ref(nd.ni_vp);
	}
#endif

	error = access1(nd.ni_vp, nd.ni_dvp, amode, &context);

#if NAMEDRSRCFORK
	if (is_namedstream) {
		vnode_rele(nd.ni_vp);
	}
#endif

 	vnode_put(nd.ni_vp);
	if (amode & _DELETE_OK)
 		vnode_put(nd.ni_dvp);
  	nameidone(&nd);

out:
	if (!(flag & AT_EACCESS))
		kauth_cred_unref(&context.vc_ucred);
	return (error);
}