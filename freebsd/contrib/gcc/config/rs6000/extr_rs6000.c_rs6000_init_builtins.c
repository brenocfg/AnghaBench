#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* pushdecl ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ decls; } ;

/* Variables and functions */
 size_t BUILT_IN_CLOG ; 
 scalar_t__ TARGET_ALTIVEC ; 
 scalar_t__ TARGET_SPE ; 
 int /*<<< orphan*/  TYPE_DECL ; 
 void* V16QI_type_node ; 
 void* V2SF_type_node ; 
 void* V2SI_type_node ; 
 void* V4HI_type_node ; 
 void* V4SF_type_node ; 
 void* V4SI_type_node ; 
 void* V8HI_type_node ; 
 int /*<<< orphan*/  altivec_init_builtins () ; 
 void* bool_V16QI_type_node ; 
 void* bool_V4SI_type_node ; 
 void* bool_V8HI_type_node ; 
 void* bool_char_type_node ; 
 void* bool_int_type_node ; 
 void* bool_short_type_node ; 
 int /*<<< orphan*/  build_decl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 void* build_distinct_type_copy (void*) ; 
 void* build_opaque_vector_type (void*,int) ; 
 int /*<<< orphan*/  build_pointer_type (void*) ; 
 void* build_vector_type (void*,int) ; 
 scalar_t__* built_in_decls ; 
 int /*<<< orphan*/  copy_node (void*) ; 
 void* float_type_internal_node ; 
 void* float_type_node ; 
 int /*<<< orphan*/  get_identifier (char*) ; 
 void* intHI_type_internal_node ; 
 void* intHI_type_node ; 
 void* intQI_type_internal_node ; 
 void* intQI_type_node ; 
 void* intSI_type_internal_node ; 
 void* intSI_type_node ; 
 TYPE_2__ lang_hooks ; 
 int /*<<< orphan*/  long_integer_type_internal_node ; 
 int /*<<< orphan*/  long_integer_type_node ; 
 int /*<<< orphan*/  long_unsigned_type_internal_node ; 
 int /*<<< orphan*/  long_unsigned_type_node ; 
 void* opaque_V2SF_type_node ; 
 void* opaque_V2SI_type_node ; 
 int /*<<< orphan*/  opaque_V4SI_type_node ; 
 int /*<<< orphan*/  opaque_p_V2SI_type_node ; 
 void* pixel_V8HI_type_node ; 
 void* pixel_type_node ; 
 int /*<<< orphan*/  rs6000_common_init_builtins () ; 
 int /*<<< orphan*/  set_user_assembler_name (scalar_t__,char*) ; 
 int /*<<< orphan*/  spe_init_builtins () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ) ; 
 void* uintHI_type_internal_node ; 
 void* uintQI_type_internal_node ; 
 void* uintSI_type_internal_node ; 
 void* unsigned_V16QI_type_node ; 
 void* unsigned_V4SI_type_node ; 
 void* unsigned_V8HI_type_node ; 
 void* unsigned_intHI_type_node ; 
 void* unsigned_intQI_type_node ; 
 void* unsigned_intSI_type_node ; 
 int /*<<< orphan*/  void_type_internal_node ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
rs6000_init_builtins (void)
{
  V2SI_type_node = build_vector_type (intSI_type_node, 2);
  V2SF_type_node = build_vector_type (float_type_node, 2);
  V4HI_type_node = build_vector_type (intHI_type_node, 4);
  V4SI_type_node = build_vector_type (intSI_type_node, 4);
  V4SF_type_node = build_vector_type (float_type_node, 4);
  V8HI_type_node = build_vector_type (intHI_type_node, 8);
  V16QI_type_node = build_vector_type (intQI_type_node, 16);

  unsigned_V16QI_type_node = build_vector_type (unsigned_intQI_type_node, 16);
  unsigned_V8HI_type_node = build_vector_type (unsigned_intHI_type_node, 8);
  unsigned_V4SI_type_node = build_vector_type (unsigned_intSI_type_node, 4);

  opaque_V2SF_type_node = build_opaque_vector_type (float_type_node, 2);
  opaque_V2SI_type_node = build_opaque_vector_type (intSI_type_node, 2);
  opaque_p_V2SI_type_node = build_pointer_type (opaque_V2SI_type_node);
  opaque_V4SI_type_node = copy_node (V4SI_type_node);

  /* The 'vector bool ...' types must be kept distinct from 'vector unsigned ...'
     types, especially in C++ land.  Similarly, 'vector pixel' is distinct from
     'vector unsigned short'.  */

  bool_char_type_node = build_distinct_type_copy (unsigned_intQI_type_node);
  bool_short_type_node = build_distinct_type_copy (unsigned_intHI_type_node);
  bool_int_type_node = build_distinct_type_copy (unsigned_intSI_type_node);
  pixel_type_node = build_distinct_type_copy (unsigned_intHI_type_node);

  long_integer_type_internal_node = long_integer_type_node;
  long_unsigned_type_internal_node = long_unsigned_type_node;
  intQI_type_internal_node = intQI_type_node;
  uintQI_type_internal_node = unsigned_intQI_type_node;
  intHI_type_internal_node = intHI_type_node;
  uintHI_type_internal_node = unsigned_intHI_type_node;
  intSI_type_internal_node = intSI_type_node;
  uintSI_type_internal_node = unsigned_intSI_type_node;
  float_type_internal_node = float_type_node;
  void_type_internal_node = void_type_node;

  (*lang_hooks.decls.pushdecl) (build_decl (TYPE_DECL,
					    get_identifier ("__bool char"),
					    bool_char_type_node));
  (*lang_hooks.decls.pushdecl) (build_decl (TYPE_DECL,
					    get_identifier ("__bool short"),
					    bool_short_type_node));
  (*lang_hooks.decls.pushdecl) (build_decl (TYPE_DECL,
					    get_identifier ("__bool int"),
					    bool_int_type_node));
  (*lang_hooks.decls.pushdecl) (build_decl (TYPE_DECL,
					    get_identifier ("__pixel"),
					    pixel_type_node));

  bool_V16QI_type_node = build_vector_type (bool_char_type_node, 16);
  bool_V8HI_type_node = build_vector_type (bool_short_type_node, 8);
  bool_V4SI_type_node = build_vector_type (bool_int_type_node, 4);
  pixel_V8HI_type_node = build_vector_type (pixel_type_node, 8);

  (*lang_hooks.decls.pushdecl) (build_decl (TYPE_DECL,
					    get_identifier ("__vector unsigned char"),
					    unsigned_V16QI_type_node));
  (*lang_hooks.decls.pushdecl) (build_decl (TYPE_DECL,
					    get_identifier ("__vector signed char"),
					    V16QI_type_node));
  (*lang_hooks.decls.pushdecl) (build_decl (TYPE_DECL,
					    get_identifier ("__vector __bool char"),
					    bool_V16QI_type_node));

  (*lang_hooks.decls.pushdecl) (build_decl (TYPE_DECL,
					    get_identifier ("__vector unsigned short"),
					    unsigned_V8HI_type_node));
  (*lang_hooks.decls.pushdecl) (build_decl (TYPE_DECL,
					    get_identifier ("__vector signed short"),
					    V8HI_type_node));
  (*lang_hooks.decls.pushdecl) (build_decl (TYPE_DECL,
					    get_identifier ("__vector __bool short"),
					    bool_V8HI_type_node));

  (*lang_hooks.decls.pushdecl) (build_decl (TYPE_DECL,
					    get_identifier ("__vector unsigned int"),
					    unsigned_V4SI_type_node));
  (*lang_hooks.decls.pushdecl) (build_decl (TYPE_DECL,
					    get_identifier ("__vector signed int"),
					    V4SI_type_node));
  (*lang_hooks.decls.pushdecl) (build_decl (TYPE_DECL,
					    get_identifier ("__vector __bool int"),
					    bool_V4SI_type_node));

  (*lang_hooks.decls.pushdecl) (build_decl (TYPE_DECL,
					    get_identifier ("__vector float"),
					    V4SF_type_node));
  (*lang_hooks.decls.pushdecl) (build_decl (TYPE_DECL,
					    get_identifier ("__vector __pixel"),
					    pixel_V8HI_type_node));

  if (TARGET_SPE)
    spe_init_builtins ();
  if (TARGET_ALTIVEC)
    altivec_init_builtins ();
  if (TARGET_ALTIVEC || TARGET_SPE)
    rs6000_common_init_builtins ();

#if TARGET_XCOFF
  /* AIX libm provides clog as __clog.  */
  if (built_in_decls [BUILT_IN_CLOG])
    set_user_assembler_name (built_in_decls [BUILT_IN_CLOG], "__clog");
#endif
}