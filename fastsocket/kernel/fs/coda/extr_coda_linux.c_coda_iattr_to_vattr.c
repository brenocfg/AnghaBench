#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* vuid_t ;
typedef  void* vgid_t ;
typedef  void* time_t ;
struct TYPE_6__ {void* tv_nsec; void* tv_sec; } ;
struct TYPE_5__ {void* tv_nsec; void* tv_sec; } ;
struct TYPE_4__ {void* tv_nsec; void* tv_sec; } ;
struct iattr {int ia_mode; unsigned int ia_valid; TYPE_3__ ia_ctime; TYPE_2__ ia_mtime; TYPE_1__ ia_atime; scalar_t__ ia_size; scalar_t__ ia_gid; scalar_t__ ia_uid; } ;
struct coda_vattr {int va_mode; int va_fileid; int va_gen; int va_bytes; int va_nlink; int va_blocksize; int va_rdev; TYPE_3__ va_ctime; TYPE_2__ va_mtime; TYPE_1__ va_atime; scalar_t__ va_size; void* va_gid; void* va_uid; void* va_type; scalar_t__ va_flags; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 unsigned int ATTR_ATIME ; 
 unsigned int ATTR_CTIME ; 
 unsigned int ATTR_GID ; 
 unsigned int ATTR_MODE ; 
 unsigned int ATTR_MTIME ; 
 unsigned int ATTR_SIZE ; 
 unsigned int ATTR_UID ; 
 void* C_VDIR ; 
 void* C_VLNK ; 
 void* C_VNON ; 
 void* C_VREG ; 
 scalar_t__ S_ISDIR (int) ; 
 scalar_t__ S_ISLNK (int) ; 
 scalar_t__ S_ISREG (int) ; 
 int mode ; 

void coda_iattr_to_vattr(struct iattr *iattr, struct coda_vattr *vattr)
{
        unsigned int valid;

        /* clean out */        
	vattr->va_mode = -1;
        vattr->va_uid = (vuid_t) -1; 
        vattr->va_gid = (vgid_t) -1;
        vattr->va_size = (off_t) -1;
	vattr->va_atime.tv_sec = (time_t) -1;
	vattr->va_atime.tv_nsec =  (time_t) -1;
        vattr->va_mtime.tv_sec = (time_t) -1;
        vattr->va_mtime.tv_nsec = (time_t) -1;
	vattr->va_ctime.tv_sec = (time_t) -1;
	vattr->va_ctime.tv_nsec = (time_t) -1;
        vattr->va_type = C_VNON;
	vattr->va_fileid = -1;
	vattr->va_gen = -1;
	vattr->va_bytes = -1;
	vattr->va_nlink = -1;
	vattr->va_blocksize = -1;
	vattr->va_rdev = -1;
        vattr->va_flags = 0;

        /* determine the type */
#if 0
        mode = iattr->ia_mode;
                if ( S_ISDIR(mode) ) {
                vattr->va_type = C_VDIR; 
        } else if ( S_ISREG(mode) ) {
                vattr->va_type = C_VREG;
        } else if ( S_ISLNK(mode) ) {
                vattr->va_type = C_VLNK;
        } else {
                /* don't do others */
                vattr->va_type = C_VNON;
        }
#endif 

        /* set those vattrs that need change */
        valid = iattr->ia_valid;
        if ( valid & ATTR_MODE ) {
                vattr->va_mode = iattr->ia_mode;
	}
        if ( valid & ATTR_UID ) {
                vattr->va_uid = (vuid_t) iattr->ia_uid;
	}
        if ( valid & ATTR_GID ) {
                vattr->va_gid = (vgid_t) iattr->ia_gid;
	}
        if ( valid & ATTR_SIZE ) {
                vattr->va_size = iattr->ia_size;
	}
        if ( valid & ATTR_ATIME ) {
                vattr->va_atime = iattr->ia_atime;
	}
        if ( valid & ATTR_MTIME ) {
                vattr->va_mtime = iattr->ia_mtime;
	}
        if ( valid & ATTR_CTIME ) {
                vattr->va_ctime = iattr->ia_ctime;
	}
}