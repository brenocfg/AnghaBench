#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uid_t ;
struct vnode_attr {int va_active; int va_vaflags; int va_mode; scalar_t__ va_uid; int va_flags; TYPE_6__* va_acl; int /*<<< orphan*/  va_guuid; int /*<<< orphan*/  va_gid; int /*<<< orphan*/  va_uuuid; } ;
struct kauth_ace {int dummy; } ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  int kauth_action_t ;
typedef  int /*<<< orphan*/  guid_t ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_8__ {int acl_entrycount; int /*<<< orphan*/ * acl_ace; } ;
struct TYPE_7__ {int /*<<< orphan*/  v_mount; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int EISDIR ; 
 int EPERM ; 
 int /*<<< orphan*/  KAUTH_DEBUG (char*,...) ; 
 int KAUTH_VNODE_CHECKIMMUTABLE ; 
 int KAUTH_VNODE_NOIMMUTABLE ; 
 int KAUTH_VNODE_TAKE_OWNERSHIP ; 
 int KAUTH_VNODE_WRITE_ATTRIBUTES ; 
 int KAUTH_VNODE_WRITE_DATA ; 
 int KAUTH_VNODE_WRITE_SECURITY ; 
 int SF_SETTABLE ; 
 int S_ISGID ; 
 int S_ISUID ; 
 int UF_SETTABLE ; 
 int /*<<< orphan*/  VATTR_INIT (struct vnode_attr*) ; 
 scalar_t__ VATTR_IS_ACTIVE (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ VATTR_IS_SUPPORTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VATTR_SET (struct vnode_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  VATTR_WANTED (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 int VA_UTIMES_NULL ; 
 int VNODE_ATTR_RDONLY ; 
 int /*<<< orphan*/  kauth_acl_free (TYPE_6__*) ; 
 int kauth_cred_getguid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 scalar_t__ kauth_cred_gid2guid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kauth_cred_ismember_gid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int kauth_cred_ismember_guid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int kauth_cred_issuser (int /*<<< orphan*/ ) ; 
 scalar_t__ kauth_cred_uid2guid (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ kauth_guid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kauth_null_guid ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  va_access_time ; 
 int /*<<< orphan*/  va_acl ; 
 int /*<<< orphan*/  va_addedtime ; 
 int /*<<< orphan*/  va_backup_time ; 
 int /*<<< orphan*/  va_change_time ; 
 int /*<<< orphan*/  va_create_time ; 
 int /*<<< orphan*/  va_data_size ; 
 int /*<<< orphan*/  va_encoding ; 
 int /*<<< orphan*/  va_flags ; 
 int /*<<< orphan*/  va_gid ; 
 int /*<<< orphan*/  va_guuid ; 
 int /*<<< orphan*/  va_mode ; 
 int /*<<< orphan*/  va_modify_time ; 
 int /*<<< orphan*/  va_uid ; 
 int /*<<< orphan*/  va_uuuid ; 
 scalar_t__ vauth_node_owner (struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ vfs_authopaque (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_context_ucred (int /*<<< orphan*/ ) ; 
 int vnode_getattr (TYPE_1__*,struct vnode_attr*,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_isdir (TYPE_1__*) ; 
 int /*<<< orphan*/  vnode_isreg (TYPE_1__*) ; 

int
vnode_authattr(vnode_t vp, struct vnode_attr *vap, kauth_action_t *actionp, vfs_context_t ctx)
{
	struct vnode_attr ova;
	kauth_action_t	required_action;
	int		error, has_priv_suser, ismember, chowner, chgroup, clear_suid, clear_sgid;
	guid_t		changer;
	gid_t		group;
	uid_t		owner;
	mode_t		newmode;
	kauth_cred_t	cred;
	uint32_t	fdelta;

	VATTR_INIT(&ova);
	required_action = 0;
	error = 0;

	/*
	 * Quickly check for enforcement applicability.
	 */
	if (vfs_authopaque(vp->v_mount))
		goto out;
	
	/*
	 * Check for attempts to set nonsensical fields.
	 */
	if (vap->va_active & VNODE_ATTR_RDONLY) {
		KAUTH_DEBUG("ATTR - ERROR: attempt to set readonly attribute(s)");
		error = EINVAL;
		goto out;
	}

	/*
	 * We need to know if the caller is the superuser.
	 */
	cred = vfs_context_ucred(ctx);
	has_priv_suser = kauth_cred_issuser(cred);
	
	/*
	 * If any of the following are changing, we need information from the old file:
	 * va_uid
	 * va_gid
	 * va_mode
	 * va_uuuid
	 * va_guuid
	 */
	if (VATTR_IS_ACTIVE(vap, va_uid) ||
	    VATTR_IS_ACTIVE(vap, va_gid) ||
	    VATTR_IS_ACTIVE(vap, va_mode) ||
	    VATTR_IS_ACTIVE(vap, va_uuuid) ||
	    VATTR_IS_ACTIVE(vap, va_guuid)) {
		VATTR_WANTED(&ova, va_mode);
		VATTR_WANTED(&ova, va_uid);
		VATTR_WANTED(&ova, va_gid);
		VATTR_WANTED(&ova, va_uuuid);
		VATTR_WANTED(&ova, va_guuid);
		KAUTH_DEBUG("ATTR - security information changing, fetching existing attributes");
	}

	/*
	 * If timestamps are being changed, we need to know who the file is owned
	 * by.
	 */
	if (VATTR_IS_ACTIVE(vap, va_create_time) ||
	    VATTR_IS_ACTIVE(vap, va_change_time) ||
	    VATTR_IS_ACTIVE(vap, va_modify_time) ||
	    VATTR_IS_ACTIVE(vap, va_access_time) ||
	    VATTR_IS_ACTIVE(vap, va_backup_time) ||
	    VATTR_IS_ACTIVE(vap, va_addedtime)) {

		VATTR_WANTED(&ova, va_uid);
#if 0	/* enable this when we support UUIDs as official owners */
		VATTR_WANTED(&ova, va_uuuid);
#endif
		KAUTH_DEBUG("ATTR - timestamps changing, fetching uid and GUID");
	}
		
	/*
	 * If flags are being changed, we need the old flags.
	 */
	if (VATTR_IS_ACTIVE(vap, va_flags)) {
		KAUTH_DEBUG("ATTR - flags changing, fetching old flags");
		VATTR_WANTED(&ova, va_flags);
	}

	/*
	 * If ACLs are being changed, we need the old ACLs.
	 */
	if (VATTR_IS_ACTIVE(vap, va_acl)) {
		KAUTH_DEBUG("ATTR - acl changing, fetching old flags");
		VATTR_WANTED(&ova, va_acl);
	}

	/*
	 * If the size is being set, make sure it's not a directory.
	 */
	if (VATTR_IS_ACTIVE(vap, va_data_size)) {
		/* size is only meaningful on regular files, don't permit otherwise */
		if (!vnode_isreg(vp)) {
			KAUTH_DEBUG("ATTR - ERROR: size change requested on non-file");
			error = vnode_isdir(vp) ? EISDIR : EINVAL;
			goto out;
		}
	}

	/*
	 * Get old data.
	 */
	KAUTH_DEBUG("ATTR - fetching old attributes %016llx", ova.va_active);
	if ((error = vnode_getattr(vp, &ova, ctx)) != 0) {
		KAUTH_DEBUG("  ERROR - got %d trying to get attributes", error);
		goto out;
	}

	/*
	 * Size changes require write access to the file data.
	 */
	if (VATTR_IS_ACTIVE(vap, va_data_size)) {
		/* if we can't get the size, or it's different, we need write access */
			KAUTH_DEBUG("ATTR - size change, requiring WRITE_DATA");
			required_action |= KAUTH_VNODE_WRITE_DATA;
	}

	/*
	 * Changing timestamps?
	 *
	 * Note that we are only called to authorize user-requested time changes;
	 * side-effect time changes are not authorized.  Authorisation is only
	 * required for existing files.
	 *
	 * Non-owners are not permitted to change the time on an existing
	 * file to anything other than the current time.
	 */
	if (VATTR_IS_ACTIVE(vap, va_create_time) ||
	    VATTR_IS_ACTIVE(vap, va_change_time) ||
	    VATTR_IS_ACTIVE(vap, va_modify_time) ||
	    VATTR_IS_ACTIVE(vap, va_access_time) ||
	    VATTR_IS_ACTIVE(vap, va_backup_time) ||
	    VATTR_IS_ACTIVE(vap, va_addedtime)) {
		/*
		 * The owner and root may set any timestamps they like,
		 * provided that the file is not immutable.  The owner still needs
		 * WRITE_ATTRIBUTES (implied by ownership but still deniable).
		 */
		if (has_priv_suser || vauth_node_owner(&ova, cred)) {
			KAUTH_DEBUG("ATTR - root or owner changing timestamps");
			required_action |= KAUTH_VNODE_CHECKIMMUTABLE | KAUTH_VNODE_WRITE_ATTRIBUTES;
		} else {
			/* just setting the current time? */
			if (vap->va_vaflags & VA_UTIMES_NULL) {
				KAUTH_DEBUG("ATTR - non-root/owner changing timestamps, requiring WRITE_ATTRIBUTES");
				required_action |= KAUTH_VNODE_WRITE_ATTRIBUTES;
			} else {
				KAUTH_DEBUG("ATTR - ERROR: illegal timestamp modification attempted");
				error = EACCES;
				goto out;
			}
		}
	}

	/*
	 * Changing file mode?
	 */
	if (VATTR_IS_ACTIVE(vap, va_mode) && VATTR_IS_SUPPORTED(&ova, va_mode) && (ova.va_mode != vap->va_mode)) {
		KAUTH_DEBUG("ATTR - mode change from %06o to %06o", ova.va_mode, vap->va_mode);

		/*
		 * Mode changes always have the same basic auth requirements.
		 */
		if (has_priv_suser) {
			KAUTH_DEBUG("ATTR - superuser mode change, requiring immutability check");
			required_action |= KAUTH_VNODE_CHECKIMMUTABLE;
		} else {
			/* need WRITE_SECURITY */
			KAUTH_DEBUG("ATTR - non-superuser mode change, requiring WRITE_SECURITY");
			required_action |= KAUTH_VNODE_WRITE_SECURITY;
		}

		/*
		 * Can't set the setgid bit if you're not in the group and not root.  Have to have
		 * existing group information in the case we're not setting it right now.
		 */
		if (vap->va_mode & S_ISGID) {
			required_action |= KAUTH_VNODE_CHECKIMMUTABLE;	/* always required */
			if (!has_priv_suser) {
				if (VATTR_IS_ACTIVE(vap, va_gid)) {
					group = vap->va_gid;
				} else if (VATTR_IS_SUPPORTED(&ova, va_gid)) {
					group = ova.va_gid;
				} else {
					KAUTH_DEBUG("ATTR - ERROR: setgid but no gid available");
					error = EINVAL;
					goto out;
				}
				/*
				 * This might be too restrictive; WRITE_SECURITY might be implied by
				 * membership in this case, rather than being an additional requirement.
				 */
				if ((error = kauth_cred_ismember_gid(cred, group, &ismember)) != 0) {
					KAUTH_DEBUG("ATTR - ERROR: got %d checking for membership in %d", error, vap->va_gid);
					goto out;
				}
				if (!ismember) {
					KAUTH_DEBUG("  DENIED - can't set SGID bit, not a member of %d", group);
					error = EPERM;
					goto out;
				}
			}
		}

		/*
		 * Can't set the setuid bit unless you're root or the file's owner.
		 */
		if (vap->va_mode & S_ISUID) {
			required_action |= KAUTH_VNODE_CHECKIMMUTABLE;	/* always required */
			if (!has_priv_suser) {
				if (VATTR_IS_ACTIVE(vap, va_uid)) {
					owner = vap->va_uid;
				} else if (VATTR_IS_SUPPORTED(&ova, va_uid)) {
					owner = ova.va_uid;
				} else {
					KAUTH_DEBUG("ATTR - ERROR: setuid but no uid available");
					error = EINVAL;
					goto out;
				}
				if (owner != kauth_cred_getuid(cred)) {
					/*
					 * We could allow this if WRITE_SECURITY is permitted, perhaps.
					 */
					KAUTH_DEBUG("ATTR - ERROR: illegal attempt to set the setuid bit");
					error = EPERM;
					goto out;
				}
			}
		}
	}
	    
	/*
	 * Validate/mask flags changes.  This checks that only the flags in
	 * the UF_SETTABLE mask are being set, and preserves the flags in
	 * the SF_SETTABLE case.
	 *
	 * Since flags changes may be made in conjunction with other changes,
	 * we will ask the auth code to ignore immutability in the case that
	 * the SF_* flags are not set and we are only manipulating the file flags.
	 * 
	 */
	if (VATTR_IS_ACTIVE(vap, va_flags)) {
		/* compute changing flags bits */
		if (VATTR_IS_SUPPORTED(&ova, va_flags)) {
			fdelta = vap->va_flags ^ ova.va_flags;
		} else {
			fdelta = vap->va_flags;
		}

		if (fdelta != 0) {
			KAUTH_DEBUG("ATTR - flags changing, requiring WRITE_SECURITY");
			required_action |= KAUTH_VNODE_WRITE_SECURITY;

			/* check that changing bits are legal */
			if (has_priv_suser) {
				/*
				 * The immutability check will prevent us from clearing the SF_*
				 * flags unless the system securelevel permits it, so just check
				 * for legal flags here.
				 */
				if (fdelta & ~(UF_SETTABLE | SF_SETTABLE)) {
					error = EPERM;
					KAUTH_DEBUG("  DENIED - superuser attempt to set illegal flag(s)");
					goto out;
				}
			} else {
				if (fdelta & ~UF_SETTABLE) {
					error = EPERM;
					KAUTH_DEBUG("  DENIED - user attempt to set illegal flag(s)");
					goto out;
				}
			}
			/*
			 * If the caller has the ability to manipulate file flags,
			 * security is not reduced by ignoring them for this operation.
			 *
			 * A more complete test here would consider the 'after' states of the flags
			 * to determine whether it would permit the operation, but this becomes
			 * very complex.
			 *
			 * Ignoring immutability is conditional on securelevel; this does not bypass
			 * the SF_* flags if securelevel > 0.
			 */
			required_action |= KAUTH_VNODE_NOIMMUTABLE;
		}
	}

	/*
	 * Validate ownership information.
	 */
	chowner = 0;
	chgroup = 0;
	clear_suid = 0;
	clear_sgid = 0;

	/*
	 * uid changing
	 * Note that if the filesystem didn't give us a UID, we expect that it doesn't
	 * support them in general, and will ignore it if/when we try to set it.
	 * We might want to clear the uid out of vap completely here.
	 */
	if (VATTR_IS_ACTIVE(vap, va_uid)) {
		if (VATTR_IS_SUPPORTED(&ova, va_uid) && (vap->va_uid != ova.va_uid)) {
		if (!has_priv_suser && (kauth_cred_getuid(cred) != vap->va_uid)) {
			KAUTH_DEBUG("  DENIED - non-superuser cannot change ownershipt to a third party");
			error = EPERM;
			goto out;
		}
		chowner = 1;
	}
		clear_suid = 1;
	}
	
	/*
	 * gid changing
	 * Note that if the filesystem didn't give us a GID, we expect that it doesn't
	 * support them in general, and will ignore it if/when we try to set it.
	 * We might want to clear the gid out of vap completely here.
	 */
	if (VATTR_IS_ACTIVE(vap, va_gid)) {
		if (VATTR_IS_SUPPORTED(&ova, va_gid) && (vap->va_gid != ova.va_gid)) {
		if (!has_priv_suser) {
			if ((error = kauth_cred_ismember_gid(cred, vap->va_gid, &ismember)) != 0) {
				KAUTH_DEBUG("  ERROR - got %d checking for membership in %d", error, vap->va_gid);
				goto out;
			}
			if (!ismember) {
				KAUTH_DEBUG("  DENIED - group change from %d to %d but not a member of target group",
				    ova.va_gid, vap->va_gid);
				error = EPERM;
				goto out;
			}
		}
		chgroup = 1;
	}
		clear_sgid = 1;
	}

	/*
	 * Owner UUID being set or changed.
	 */
	if (VATTR_IS_ACTIVE(vap, va_uuuid)) {
		/* if the owner UUID is not actually changing ... */
		if (VATTR_IS_SUPPORTED(&ova, va_uuuid)) {
			if (kauth_guid_equal(&vap->va_uuuid, &ova.va_uuuid))
				goto no_uuuid_change;
			
			/*
			 * If the current owner UUID is a null GUID, check
			 * it against the UUID corresponding to the owner UID.
			 */
			if (kauth_guid_equal(&ova.va_uuuid, &kauth_null_guid) &&
			    VATTR_IS_SUPPORTED(&ova, va_uid)) {
				guid_t uid_guid;

				if (kauth_cred_uid2guid(ova.va_uid, &uid_guid) == 0 &&
				    kauth_guid_equal(&vap->va_uuuid, &uid_guid))
				    	goto no_uuuid_change;
			}
		}
		
		/*
		 * The owner UUID cannot be set by a non-superuser to anything other than
		 * their own or a null GUID (to "unset" the owner UUID).
		 * Note that file systems must be prepared to handle the
		 * null UUID case in a manner appropriate for that file
		 * system.
		 */
		if (!has_priv_suser) {
			if ((error = kauth_cred_getguid(cred, &changer)) != 0) {
				KAUTH_DEBUG("  ERROR - got %d trying to get caller UUID", error);
				/* XXX ENOENT here - no UUID - should perhaps become EPERM */
				goto out;
			}
			if (!kauth_guid_equal(&vap->va_uuuid, &changer) &&
			    !kauth_guid_equal(&vap->va_uuuid, &kauth_null_guid)) {
				KAUTH_DEBUG("  ERROR - cannot set supplied owner UUID - not us / null");
				error = EPERM;
				goto out;
			}
		}
		chowner = 1;
		clear_suid = 1;
	}
no_uuuid_change:
	/*
	 * Group UUID being set or changed.
	 */
	if (VATTR_IS_ACTIVE(vap, va_guuid)) {
		/* if the group UUID is not actually changing ... */
		if (VATTR_IS_SUPPORTED(&ova, va_guuid)) {
			if (kauth_guid_equal(&vap->va_guuid, &ova.va_guuid))
				goto no_guuid_change;

			/*
			 * If the current group UUID is a null UUID, check
			 * it against the UUID corresponding to the group GID.
			 */
			if (kauth_guid_equal(&ova.va_guuid, &kauth_null_guid) &&
			    VATTR_IS_SUPPORTED(&ova, va_gid)) {
				guid_t gid_guid;

				if (kauth_cred_gid2guid(ova.va_gid, &gid_guid) == 0 &&
				    kauth_guid_equal(&vap->va_guuid, &gid_guid))
				    	goto no_guuid_change;
			}
		}

		/*
		 * The group UUID cannot be set by a non-superuser to anything other than
		 * one of which they are a member or a null GUID (to "unset"
		 * the group UUID).
		 * Note that file systems must be prepared to handle the
		 * null UUID case in a manner appropriate for that file
		 * system.
		 */
		if (!has_priv_suser) {
			if (kauth_guid_equal(&vap->va_guuid, &kauth_null_guid))
				ismember = 1;
			else if ((error = kauth_cred_ismember_guid(cred, &vap->va_guuid, &ismember)) != 0) {
				KAUTH_DEBUG("  ERROR - got %d trying to check group membership", error);
				goto out;
			}
			if (!ismember) {
				KAUTH_DEBUG("  ERROR - cannot set supplied group UUID - not a member / null");
				error = EPERM;
				goto out;
			}
		}
		chgroup = 1;
	}
no_guuid_change:

	/*
	 * Compute authorisation for group/ownership changes.
	 */
	if (chowner || chgroup || clear_suid || clear_sgid) {
		if (has_priv_suser) {
			KAUTH_DEBUG("ATTR - superuser changing file owner/group, requiring immutability check");
			required_action |= KAUTH_VNODE_CHECKIMMUTABLE;
		} else {
			if (chowner) {
				KAUTH_DEBUG("ATTR - ownership change, requiring TAKE_OWNERSHIP");
				required_action |= KAUTH_VNODE_TAKE_OWNERSHIP;
			}
			if (chgroup && !chowner) {
				KAUTH_DEBUG("ATTR - group change, requiring WRITE_SECURITY");
				required_action |= KAUTH_VNODE_WRITE_SECURITY;
			}
			
		}
			
		/*
		 * clear set-uid and set-gid bits. POSIX only requires this for
		 * non-privileged processes but we do it even for root.
		 */
		if (VATTR_IS_ACTIVE(vap, va_mode)) {
			newmode = vap->va_mode;
		} else if (VATTR_IS_SUPPORTED(&ova, va_mode)) {
			newmode = ova.va_mode;
		} else {
			KAUTH_DEBUG("CHOWN - trying to change owner but cannot get mode from filesystem to mask setugid bits");
			newmode = 0;
		}

		/* chown always clears setuid/gid bits. An exception is made for
		 * setattrlist executed by a root process to set <uid, gid, mode> on a file:
		 * setattrlist is allowed to set the new mode on the file and change (chown)
		 * uid/gid.
		 */
		if (newmode & (S_ISUID | S_ISGID)) {
			if (!VATTR_IS_ACTIVE(vap, va_mode) || !has_priv_suser) {
				KAUTH_DEBUG("CHOWN - masking setugid bits from mode %o to %o",
					newmode, newmode & ~(S_ISUID | S_ISGID));
				newmode &= ~(S_ISUID | S_ISGID);
			}
			VATTR_SET(vap, va_mode, newmode);
		}
	}

	/*
	 * Authorise changes in the ACL.
	 */
	if (VATTR_IS_ACTIVE(vap, va_acl)) {

		/* no existing ACL */
		if (!VATTR_IS_ACTIVE(&ova, va_acl) || (ova.va_acl == NULL)) {

			/* adding an ACL */
			if (vap->va_acl != NULL) {
				required_action |= KAUTH_VNODE_WRITE_SECURITY;
				KAUTH_DEBUG("CHMOD - adding ACL");
			}

			/* removing an existing ACL */
		} else if (vap->va_acl == NULL) {
			required_action |= KAUTH_VNODE_WRITE_SECURITY;
			KAUTH_DEBUG("CHMOD - removing ACL");

			/* updating an existing ACL */
		} else {
			if (vap->va_acl->acl_entrycount != ova.va_acl->acl_entrycount) {
				/* entry count changed, must be different */
				required_action |= KAUTH_VNODE_WRITE_SECURITY;
				KAUTH_DEBUG("CHMOD - adding/removing ACL entries");
			} else if (vap->va_acl->acl_entrycount > 0) {
				/* both ACLs have the same ACE count, said count is 1 or more, bitwise compare ACLs */
				if (memcmp(&vap->va_acl->acl_ace[0], &ova.va_acl->acl_ace[0],
					sizeof(struct kauth_ace) * vap->va_acl->acl_entrycount)) {
					required_action |= KAUTH_VNODE_WRITE_SECURITY;
					KAUTH_DEBUG("CHMOD - changing ACL entries");
				}
			}
		}
	}

	/*
	 * Other attributes that require authorisation.
	 */
	if (VATTR_IS_ACTIVE(vap, va_encoding))
		required_action |= KAUTH_VNODE_WRITE_ATTRIBUTES;
	
out:
	if (VATTR_IS_SUPPORTED(&ova, va_acl) && (ova.va_acl != NULL))
		kauth_acl_free(ova.va_acl);
	if (error == 0)
		*actionp = required_action;
	return(error);
}