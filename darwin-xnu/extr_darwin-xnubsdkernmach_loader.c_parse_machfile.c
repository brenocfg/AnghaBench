#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t vm_size_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int /*<<< orphan*/  vm_map_offset_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;
struct vnode {char* v_name; } ;
struct uuid_command {int dummy; } ;
struct thread_command {int dummy; } ;
struct segment_command_64 {int initprot; int /*<<< orphan*/  filesize; int /*<<< orphan*/  fileoff; int /*<<< orphan*/  segname; int /*<<< orphan*/  vmaddr; } ;
struct segment_command {int initprot; int /*<<< orphan*/  filesize; int /*<<< orphan*/  fileoff; int /*<<< orphan*/  segname; int /*<<< orphan*/  vmaddr; } ;
struct mach_header_64 {int dummy; } ;
struct mach_header {scalar_t__ magic; int cputype; int cpusubtype; int filetype; int sizeofcmds; int flags; int /*<<< orphan*/  ncmds; } ;
struct load_command {int cmdsize; int cmd; } ;
struct linkedit_data_command {int dummy; } ;
struct image_params {int dummy; } ;
struct entry_point_command {int dummy; } ;
struct dylinker_command {int dummy; } ;
typedef  TYPE_1__* proc_t ;
typedef  scalar_t__ off_t ;
typedef  scalar_t__ load_return_t ;
struct TYPE_14__ {scalar_t__ validentry; int csflags; scalar_t__ thread_count; scalar_t__ needs_dynlinker; int /*<<< orphan*/  using_lcmain; scalar_t__ max_vm_addr; } ;
typedef  TYPE_2__ load_result_t ;
typedef  int integer_t ;
typedef  scalar_t__ int64_t ;
typedef  int cpu_type_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_13__ {int p_pid; } ;

/* Variables and functions */
 int CPU_ARCH_ABI64 ; 
 int CPU_ARCH_MASK ; 
 int CPU_SUBTYPE_MASK ; 
 int CPU_TYPE_X86 ; 
 int CS_ENFORCEMENT ; 
 int CS_HARD ; 
 int CS_KILL ; 
 int CS_VALID ; 
 unsigned int CS_VALIDATE_TAINTED ; 
 scalar_t__ FALSE ; 
#define  LC_CODE_SIGNATURE 136 
#define  LC_LOAD_DYLINKER 135 
#define  LC_MAIN 134 
#define  LC_SEGMENT 133 
#define  LC_SEGMENT_64 132 
#define  LC_UNIXTHREAD 131 
#define  LC_UUID 130 
 scalar_t__ LOAD_BADARCH ; 
 scalar_t__ LOAD_BADARCH_X86 ; 
 scalar_t__ LOAD_BADMACHO ; 
 scalar_t__ LOAD_BADMACHO_UPX ; 
 scalar_t__ LOAD_FAILURE ; 
 scalar_t__ LOAD_IOERROR ; 
 scalar_t__ LOAD_NOSPACE ; 
 scalar_t__ LOAD_SUCCESS ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MH_CIGAM_64 ; 
#define  MH_DYLINKER 129 
#define  MH_EXECUTE 128 
 scalar_t__ MH_MAGIC_64 ; 
 int MH_PIE ; 
 int /*<<< orphan*/  PAGE_MASK ; 
 size_t PAGE_SIZE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UBC_FLAGS_NONE ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 scalar_t__ bootarg_no32exec ; 
 int cpu_type () ; 
 int cs_debug ; 
 scalar_t__ cs_process_global_enforcement () ; 
 scalar_t__ cs_validate_range (struct vnode*,int /*<<< orphan*/ *,scalar_t__,void*,size_t,unsigned int*) ; 
 TYPE_1__* current_proc () ; 
 int /*<<< orphan*/  grade_binary (int,int) ; 
 void* kalloc (size_t) ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int /*<<< orphan*/  kfree (void*,size_t) ; 
 scalar_t__ load_code_signature (struct linkedit_data_command*,struct vnode*,scalar_t__,scalar_t__,int,TYPE_2__*,struct image_params*) ; 
 scalar_t__ load_dylinker (struct dylinker_command*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,TYPE_2__*,struct image_params*) ; 
 scalar_t__ load_main (struct entry_point_command*,int /*<<< orphan*/ ,scalar_t__,TYPE_2__*) ; 
 scalar_t__ load_segment (struct load_command*,int,void*,scalar_t__,scalar_t__,struct vnode*,int /*<<< orphan*/ ,scalar_t__,TYPE_2__*) ; 
 scalar_t__ load_unixthread (struct thread_command*,int /*<<< orphan*/ ,scalar_t__,TYPE_2__*) ; 
 scalar_t__ load_uuid (struct uuid_command*,char*,TYPE_2__*) ; 
 scalar_t__ os_add_overflow (size_t,int,size_t*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ round_page_overflow (size_t,size_t*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  thread_state_initialize (int /*<<< orphan*/ ) ; 
 void* ubc_getobject (struct vnode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_page_mask (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_round_page (scalar_t__,int /*<<< orphan*/ ) ; 
 int vn_rdwr (int /*<<< orphan*/ ,struct vnode*,void*,size_t,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,TYPE_1__*) ; 

__attribute__((used)) static
load_return_t
parse_machfile(
	struct vnode 		*vp,       
	vm_map_t		map,
	thread_t		thread,
	struct mach_header	*header,
	off_t			file_offset,
	off_t			macho_size,
	int			depth,
	int64_t			aslr_offset,
	int64_t			dyld_aslr_offset,
	load_result_t		*result,
	load_result_t		*binresult,
	struct image_params	*imgp
)
{
	uint32_t		ncmds;
	struct load_command	*lcp;
	struct dylinker_command	*dlp = 0;
	integer_t		dlarchbits = 0;
	void *			control;
	load_return_t		ret = LOAD_SUCCESS;
	void *			addr;
	vm_size_t		alloc_size, cmds_size;
	size_t			offset;
	size_t			oldoffset;	/* for overflow check */
	int			pass;
	proc_t			p = current_proc();		/* XXXX */
	int			error;
	int 			resid = 0;
	size_t			mach_header_sz = sizeof(struct mach_header);
	boolean_t		abi64;
	boolean_t		got_code_signatures = FALSE;
	boolean_t		found_header_segment = FALSE;
	boolean_t		found_xhdr = FALSE;
	int64_t			slide = 0;
	boolean_t		dyld_no_load_addr = FALSE;
	boolean_t		is_dyld = FALSE;
	vm_map_offset_t		effective_page_mask = MAX(PAGE_MASK, vm_map_page_mask(map));
#if __arm64__
	uint32_t		pagezero_end = 0;
	uint32_t		executable_end = 0;
	uint32_t		writable_start = 0;
	vm_map_size_t		effective_page_size;

	effective_page_size = MAX(PAGE_SIZE, vm_map_page_size(map));
#endif /* __arm64__ */

	if (header->magic == MH_MAGIC_64 ||
	    header->magic == MH_CIGAM_64) {
	    	mach_header_sz = sizeof(struct mach_header_64);
	}

	/*
	 *	Break infinite recursion
	 */
	if (depth > 1) {
		return(LOAD_FAILURE);
	}

	depth++;

	/*
	 *	Check to see if right machine type.
	 */
	if (((cpu_type_t)(header->cputype & ~CPU_ARCH_MASK) != (cpu_type() & ~CPU_ARCH_MASK)) ||
	    !grade_binary(header->cputype,
	    	header->cpusubtype & ~CPU_SUBTYPE_MASK))
		return(LOAD_BADARCH);

#if __x86_64__
	if (bootarg_no32exec && (header->cputype == CPU_TYPE_X86)) {
		return(LOAD_BADARCH_X86);
	}
#endif

	abi64 = ((header->cputype & CPU_ARCH_ABI64) == CPU_ARCH_ABI64);

	switch (header->filetype) {

	case MH_EXECUTE:
		if (depth != 1) {
			return (LOAD_FAILURE);
		}
#if CONFIG_EMBEDDED
		if (header->flags & MH_DYLDLINK) {
			/* Check properties of dynamic executables */
			if (!(header->flags & MH_PIE) && pie_required(header->cputype, header->cpusubtype & ~CPU_SUBTYPE_MASK)) {
				return (LOAD_FAILURE);
			}
			result->needs_dynlinker = TRUE;
		} else {
			/* Check properties of static executables (disallowed except for development) */
#if !(DEVELOPMENT || DEBUG)
			return (LOAD_FAILURE);
#endif
		}
#endif /* CONFIG_EMBEDDED */

		break;
	case MH_DYLINKER:
		if (depth != 2) {
			return (LOAD_FAILURE);
		}
		is_dyld = TRUE;
		break;
		
	default:
		return (LOAD_FAILURE);
	}

	/*
	 *	Get the pager for the file.
	 */
	control = ubc_getobject(vp, UBC_FLAGS_NONE);

	/* ensure header + sizeofcmds falls within the file */
	if (os_add_overflow(mach_header_sz, header->sizeofcmds, &cmds_size) ||
			(off_t)cmds_size > macho_size ||
			round_page_overflow(cmds_size, &alloc_size)) {
		return LOAD_BADMACHO;
	}

	/*
	 * Map the load commands into kernel memory.
	 */
	addr = kalloc(alloc_size);
	if (addr == NULL) {
		return LOAD_NOSPACE;
	}

	error = vn_rdwr(UIO_READ, vp, addr, alloc_size, file_offset,
	    UIO_SYSSPACE, 0, kauth_cred_get(), &resid, p);
	if (error) {
		kfree(addr, alloc_size);
		return LOAD_IOERROR;
	}

	if (resid) {
		/* We must be able to read in as much as the mach_header indicated */
		kfree(addr, alloc_size);
		return LOAD_BADMACHO;
	}

	/*
	 *	For PIE and dyld, slide everything by the ASLR offset.
	 */
	if ((header->flags & MH_PIE) || is_dyld) {
		slide = aslr_offset;
	}

	/*
	 *  Scan through the commands, processing each one as necessary.
	 *  We parse in three passes through the headers:
	 *  0: determine if TEXT and DATA boundary can be page-aligned
	 *  1: thread state, uuid, code signature
	 *  2: segments
	 *  3: dyld, encryption, check entry point
	 */

	boolean_t slide_realign = FALSE;
#if __arm64__
	if (!abi64) {
		slide_realign = TRUE;
	}
#endif

	for (pass = 0; pass <= 3; pass++) {

		if (pass == 0 && !slide_realign && !is_dyld) {
			/* if we dont need to realign the slide or determine dyld's load
			 * address, pass 0 can be skipped */
			continue;
		} else if (pass == 1) {
#if __arm64__
			boolean_t	is_pie;
			int64_t		adjust;

			is_pie = ((header->flags & MH_PIE) != 0);
			if (pagezero_end != 0 &&
			    pagezero_end < effective_page_size) {
				/* need at least 1 page for PAGEZERO */
				adjust = effective_page_size;
				MACHO_PRINTF(("pagezero boundary at "
					      "0x%llx; adjust slide from "
					      "0x%llx to 0x%llx%s\n",
					      (uint64_t) pagezero_end,
					      slide,
					      slide + adjust,
					      (is_pie
					       ? ""
					       : " BUT NO PIE ****** :-(")));
				if (is_pie) {
					slide += adjust;
					pagezero_end += adjust;
					executable_end += adjust;
					writable_start += adjust;
				}
			}
			if (pagezero_end != 0) {
				result->has_pagezero = TRUE;
			}
			if (executable_end == writable_start && 
			    (executable_end & effective_page_mask) != 0 &&
			    (executable_end & FOURK_PAGE_MASK) == 0) {

				/*
				 * The TEXT/DATA boundary is 4K-aligned but
				 * not page-aligned.  Adjust the slide to make
				 * it page-aligned and avoid having a page
				 * with both write and execute permissions.
				 */
				adjust =
					(effective_page_size -
					 (executable_end & effective_page_mask));
				MACHO_PRINTF(("page-unaligned X-W boundary at "
					      "0x%llx; adjust slide from "
					      "0x%llx to 0x%llx%s\n",
					      (uint64_t) executable_end,
					      slide,
					      slide + adjust,
					      (is_pie
					       ? ""
					       : " BUT NO PIE ****** :-(")));
				if (is_pie)
					slide += adjust;
			}
#endif /* __arm64__ */

			if (dyld_no_load_addr && binresult) {
				/*
				 * The dyld Mach-O does not specify a load address. Try to locate
				 * it right after the main binary. If binresult == NULL, load
				 * directly to the given slide.
				 */
				slide = vm_map_round_page(slide + binresult->max_vm_addr, effective_page_mask);
			}
		}

		/*
		 * Check that the entry point is contained in an executable segments
		 */ 
		if ((pass == 3) && (!result->using_lcmain && result->validentry == 0)) {
			thread_state_initialize(thread);
			ret = LOAD_FAILURE;
			break;
		}

		/*
		 * Check that some segment maps the start of the mach-o file, which is
		 * needed by the dynamic loader to read the mach headers, etc.
		 */
		if ((pass == 3) && (found_header_segment == FALSE)) {
			ret = LOAD_BADMACHO;
			break;
		}

		/*
		 * Loop through each of the load_commands indicated by the
		 * Mach-O header; if an absurd value is provided, we just
		 * run off the end of the reserved section by incrementing
		 * the offset too far, so we are implicitly fail-safe.
		 */
		offset = mach_header_sz;
		ncmds = header->ncmds;

		while (ncmds--) {

			/* ensure enough space for a minimal load command */
			if (offset + sizeof(struct load_command) > cmds_size) {
				ret = LOAD_BADMACHO;
				break;
			}

			/*
			 *	Get a pointer to the command.
			 */
			lcp = (struct load_command *)(addr + offset);
			oldoffset = offset;

			/*
			 * Perform prevalidation of the struct load_command
			 * before we attempt to use its contents.  Invalid
			 * values are ones which result in an overflow, or
			 * which can not possibly be valid commands, or which
			 * straddle or exist past the reserved section at the
			 * start of the image.
			 */
			if (os_add_overflow(offset, lcp->cmdsize, &offset) ||
					lcp->cmdsize < sizeof(struct load_command) ||
					offset > cmds_size) {
				ret = LOAD_BADMACHO;
				break;
			}

			/*
			 * Act on struct load_command's for which kernel
			 * intervention is required.
			 */
			switch(lcp->cmd) {
			case LC_SEGMENT: {
				struct segment_command *scp = (struct segment_command *) lcp;
				if (pass == 0) {
					if (is_dyld && scp->vmaddr == 0 && scp->fileoff == 0) {
						dyld_no_load_addr = TRUE;
						if (!slide_realign) {
							/* got what we need, bail early on pass 0 */
							continue;
						}
					}

#if __arm64__
					assert(!abi64);

					if (scp->initprot == 0 && scp->maxprot == 0 && scp->vmaddr == 0) {
						/* PAGEZERO */
						if (os_add3_overflow(scp->vmaddr, scp->vmsize, slide, &pagezero_end)) {
							ret = LOAD_BADMACHO;
							break;
						}
					}
					if (scp->initprot & VM_PROT_EXECUTE) {
						/* TEXT */
						if (os_add3_overflow(scp->vmaddr, scp->vmsize, slide, &executable_end)) {
							ret = LOAD_BADMACHO;
							break;
						}
					}
					if (scp->initprot & VM_PROT_WRITE) {
						/* DATA */
						if (os_add_overflow(scp->vmaddr, slide, &writable_start)) {
							ret = LOAD_BADMACHO;
							break;
						}
					}
#endif /* __arm64__ */
					break;
				}

				if (pass == 1 && !strncmp(scp->segname, "__XHDR", sizeof(scp->segname))) {
					found_xhdr = TRUE;
				}

				if (pass != 2)
					break;

				if (abi64) {
					/*
					 * Having an LC_SEGMENT command for the
					 * wrong ABI is invalid <rdar://problem/11021230>
					 */
					ret = LOAD_BADMACHO;
					break;
				}

				ret = load_segment(lcp,
				                   header->filetype,
				                   control,
				                   file_offset,
				                   macho_size,
				                   vp,
				                   map,
				                   slide,
				                   result);
				if (ret == LOAD_SUCCESS && scp->fileoff == 0 && scp->filesize > 0) {
					/* Enforce a single segment mapping offset zero, with R+X
					 * protection. */
					if (found_header_segment ||
							((scp->initprot & (VM_PROT_READ|VM_PROT_EXECUTE)) != (VM_PROT_READ|VM_PROT_EXECUTE))) {
						ret = LOAD_BADMACHO;
						break;
					}
					found_header_segment = TRUE;
				}

				break;
			}
			case LC_SEGMENT_64: {
				struct segment_command_64 *scp64 = (struct segment_command_64 *) lcp;

				if (pass == 0) {
					if (is_dyld && scp64->vmaddr == 0 && scp64->fileoff == 0) {
						dyld_no_load_addr = TRUE;
						if (!slide_realign) {
							/* got what we need, bail early on pass 0 */
							continue;
						}
					}
				}

				if (pass == 1 && !strncmp(scp64->segname, "__XHDR", sizeof(scp64->segname))) {
					found_xhdr = TRUE;
				}

				if (pass != 2)
					break;

				if (!abi64) {
					/*
					 * Having an LC_SEGMENT_64 command for the
					 * wrong ABI is invalid <rdar://problem/11021230>
					 */
					ret = LOAD_BADMACHO;
					break;
				}

				ret = load_segment(lcp,
				                   header->filetype,
				                   control,
				                   file_offset,
				                   macho_size,
				                   vp,
				                   map,
				                   slide,
				                   result);

				if (ret == LOAD_SUCCESS && scp64->fileoff == 0 && scp64->filesize > 0) {
					/* Enforce a single segment mapping offset zero, with R+X
					 * protection. */
					if (found_header_segment ||
							((scp64->initprot & (VM_PROT_READ|VM_PROT_EXECUTE)) != (VM_PROT_READ|VM_PROT_EXECUTE))) {
						ret = LOAD_BADMACHO;
						break;
					}
					found_header_segment = TRUE;
				}

				break;
			}
			case LC_UNIXTHREAD:
				if (pass != 1)
					break;
				ret = load_unixthread(
						 (struct thread_command *) lcp,
						 thread,
						 slide,
						 result);
				break;
			case LC_MAIN:
				if (pass != 1)
					break;
				if (depth != 1)
					break;
				ret = load_main(
						 (struct entry_point_command *) lcp,
						 thread,
						 slide,
						 result);
				break;
			case LC_LOAD_DYLINKER:
				if (pass != 3)
					break;
				if ((depth == 1) && (dlp == 0)) {
					dlp = (struct dylinker_command *)lcp;
					dlarchbits = (header->cputype & CPU_ARCH_MASK);
				} else {
					ret = LOAD_FAILURE;
				}
				break;
			case LC_UUID:
				if (pass == 1 && depth == 1) {
					ret = load_uuid((struct uuid_command *) lcp,
							(char *)addr + cmds_size,
							result);
				}
				break;
			case LC_CODE_SIGNATURE:
				/* CODE SIGNING */
				if (pass != 1)
					break;
				/* pager -> uip ->
				   load signatures & store in uip
				   set VM object "signed_pages"
				*/
				ret = load_code_signature(
					(struct linkedit_data_command *) lcp,
					vp,
					file_offset,
					macho_size,
					header->cputype,
					result,
					imgp);
				if (ret != LOAD_SUCCESS) {
					printf("proc %d: load code signature error %d "
					       "for file \"%s\"\n",
					       p->p_pid, ret, vp->v_name);
					/*
					 * Allow injections to be ignored on devices w/o enforcement enabled
					 */
					if (!cs_process_global_enforcement())
					    ret = LOAD_SUCCESS; /* ignore error */

				} else {
					got_code_signatures = TRUE;
				}

				if (got_code_signatures) {
					unsigned tainted = CS_VALIDATE_TAINTED;
					boolean_t valid = FALSE;
					vm_size_t off = 0;


					if (cs_debug > 10)
						printf("validating initial pages of %s\n", vp->v_name);
					
					while (off < alloc_size && ret == LOAD_SUCCESS) {
					     tainted = CS_VALIDATE_TAINTED;

					     valid = cs_validate_range(vp,
								       NULL,
								       file_offset + off,
								       addr + off,
								       PAGE_SIZE,
								       &tainted);
					     if (!valid || (tainted & CS_VALIDATE_TAINTED)) {
						     if (cs_debug)
							     printf("CODE SIGNING: %s[%d]: invalid initial page at offset %lld validated:%d tainted:%d csflags:0x%x\n", 
								    vp->v_name, p->p_pid, (long long)(file_offset + off), valid, tainted, result->csflags);
						     if (cs_process_global_enforcement() ||
							 (result->csflags & (CS_HARD|CS_KILL|CS_ENFORCEMENT))) {
							     ret = LOAD_FAILURE;
						     }
						     result->csflags &= ~CS_VALID;
					     }
					     off += PAGE_SIZE;
					}
				}

				break;
#if CONFIG_CODE_DECRYPTION
			case LC_ENCRYPTION_INFO:
			case LC_ENCRYPTION_INFO_64:
				if (pass != 3)
					break;
				ret = set_code_unprotect(
					(struct encryption_info_command *) lcp,
					addr, map, slide, vp, file_offset,
					header->cputype, header->cpusubtype);
				if (ret != LOAD_SUCCESS) {
					os_reason_t load_failure_reason = OS_REASON_NULL;
					printf("proc %d: set_code_unprotect() error %d "
					       "for file \"%s\"\n",
					       p->p_pid, ret, vp->v_name);
					/* 
					 * Don't let the app run if it's 
					 * encrypted but we failed to set up the
					 * decrypter. If the keys are missing it will
					 * return LOAD_DECRYPTFAIL.
					 */
					 if (ret == LOAD_DECRYPTFAIL) {
						/* failed to load due to missing FP keys */
						proc_lock(p);
						p->p_lflag |= P_LTERM_DECRYPTFAIL;
						proc_unlock(p);

						KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_PROC, BSD_PROC_EXITREASON_CREATE) | DBG_FUNC_NONE,
								p->p_pid, OS_REASON_EXEC, EXEC_EXIT_REASON_FAIRPLAY_DECRYPT, 0, 0);
						load_failure_reason = os_reason_create(OS_REASON_EXEC, EXEC_EXIT_REASON_FAIRPLAY_DECRYPT);
					 } else {

						KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_PROC, BSD_PROC_EXITREASON_CREATE) | DBG_FUNC_NONE,
								p->p_pid, OS_REASON_EXEC, EXEC_EXIT_REASON_DECRYPT, 0, 0);
						load_failure_reason = os_reason_create(OS_REASON_EXEC, EXEC_EXIT_REASON_DECRYPT);
					 }

					 assert(load_failure_reason != OS_REASON_NULL);
					 psignal_with_reason(p, SIGKILL, load_failure_reason);
				}
				break;
#endif
#if __arm64__
			case LC_VERSION_MIN_IPHONEOS: {
				struct version_min_command *vmc;

				if (pass != 1) {
					break;
				}
				vmc = (struct version_min_command *) lcp;
				if (vmc->sdk < (12 << 16)) {
					/* app built with a pre-iOS12 SDK: apply legacy footprint mitigation */
					result->legacy_footprint = TRUE;
				}
//				printf("FBDP %s:%d vp %p (%s) sdk %d.%d.%d -> legacy_footprint=%d\n", __FUNCTION__, __LINE__, vp, vp->v_name, (vmc->sdk >> 16), ((vmc->sdk & 0xFF00) >> 8), (vmc->sdk & 0xFF), result->legacy_footprint);
				break;
			}
#endif /* __arm64__ */
			default:
				/* Other commands are ignored by the kernel */
				ret = LOAD_SUCCESS;
				break;
			}
			if (ret != LOAD_SUCCESS)
				break;
		}
		if (ret != LOAD_SUCCESS)
			break;
	}

	if (ret == LOAD_SUCCESS) {
		if(!got_code_signatures && cs_process_global_enforcement()) {
			ret = LOAD_FAILURE;
		}

		/* Make sure if we need dyld, we got it */
		if (result->needs_dynlinker && !dlp) {
			ret = LOAD_FAILURE;
		}

		if ((ret == LOAD_SUCCESS) && (dlp != 0)) {
			/*
			 * load the dylinker, and slide it by the independent DYLD ASLR
			 * offset regardless of the PIE-ness of the main binary.
			 */
			ret = load_dylinker(dlp, dlarchbits, map, thread, depth,
					    dyld_aslr_offset, result, imgp);
		}

		if ((ret == LOAD_SUCCESS) && (depth == 1)) {
			if (result->thread_count == 0) {
				ret = LOAD_FAILURE;
			}
#if CONFIG_ENFORCE_SIGNED_CODE
			if (result->needs_dynlinker && !(result->csflags & CS_DYLD_PLATFORM)) {
				ret = LOAD_FAILURE;
			}
#endif
	    }
	}

	if (ret == LOAD_BADMACHO && found_xhdr) {
		ret = LOAD_BADMACHO_UPX;
	}

	kfree(addr, alloc_size);

	return ret;
}