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
typedef  int kern_return_t ;

/* Variables and functions */
 int EBUSY ; 
 int EEXIST ; 
 int EINTR ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int ENOTSUP ; 
 int EPERM ; 
 int ETIMEDOUT ; 
#define  KERN_ABORTED 138 
#define  KERN_FAILURE 137 
#define  KERN_INSUFFICIENT_BUFFER_SIZE 136 
#define  KERN_MEMORY_PRESENT 135 
#define  KERN_NOT_IN_SET 134 
#define  KERN_NOT_SUPPORTED 133 
#define  KERN_NO_ACCESS 132 
#define  KERN_NO_SPACE 131 
#define  KERN_OPERATION_TIMED_OUT 130 
#define  KERN_RESOURCE_SHORTAGE 129 
#define  KERN_SUCCESS 128 

__attribute__((used)) static int
stackshot_kern_return_to_bsd_error(kern_return_t kr)
{
	switch (kr) {
		case KERN_SUCCESS:
			return 0;
		case KERN_RESOURCE_SHORTAGE:
			/* could not allocate memory, or stackshot is actually bigger than
			 * SANE_TRACEBUF_SIZE */
			return ENOMEM;
	    case KERN_INSUFFICIENT_BUFFER_SIZE:
		case KERN_NO_SPACE:
			/* ran out of buffer to write the stackshot.  Normally this error
			 * causes a larger buffer to be allocated in-kernel, rather than
			 * being returned to the user. */
			return ENOSPC;
		case KERN_NO_ACCESS:
			return EPERM;
		case KERN_MEMORY_PRESENT:
			return EEXIST;
		case KERN_NOT_SUPPORTED:
			return ENOTSUP;
		case KERN_NOT_IN_SET:
			/* requested existing buffer, but there isn't one. */
			return ENOENT;
	    case KERN_ABORTED:
			/* kdp did not report an error, but also did not produce any data */
			return EINTR;
	    case KERN_FAILURE:
			/* stackshot came across inconsistent data and needed to bail out */
			return EBUSY;
	    case KERN_OPERATION_TIMED_OUT:
			/* debugger synchronization timed out */
			return ETIMEDOUT;
		default:
			return EINVAL;
	}
}