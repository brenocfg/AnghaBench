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
typedef  int /*<<< orphan*/ * spvc_resources ;
typedef  int /*<<< orphan*/ * spvc_parsed_ir ;
typedef  int /*<<< orphan*/ * spvc_context ;
typedef  int /*<<< orphan*/ * spvc_compiler_options ;
typedef  int /*<<< orphan*/ * spvc_compiler ;
typedef  int /*<<< orphan*/  SpvId ;

/* Variables and functions */
 int /*<<< orphan*/  SPVC_BACKEND_CPP ; 
 int /*<<< orphan*/  SPVC_BACKEND_GLSL ; 
 int /*<<< orphan*/  SPVC_BACKEND_HLSL ; 
 int /*<<< orphan*/  SPVC_BACKEND_JSON ; 
 int /*<<< orphan*/  SPVC_BACKEND_MSL ; 
 int /*<<< orphan*/  SPVC_BACKEND_NONE ; 
 int /*<<< orphan*/  SPVC_CAPTURE_MODE_COPY ; 
 int /*<<< orphan*/  SPVC_CAPTURE_MODE_TAKE_OWNERSHIP ; 
 int /*<<< orphan*/  SPVC_CHECKED_CALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPVC_CHECKED_CALL_NEGATIVE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPVC_COMPILER_OPTION_HLSL_SHADER_MODEL ; 
 int /*<<< orphan*/  SPVC_COMPILER_OPTION_MSL_PLATFORM ; 
 int /*<<< orphan*/  compile (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dump_resources (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 scalar_t__ read_file (char*,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  spvc_compiler_create_compiler_options (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  spvc_compiler_create_shader_resources (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  spvc_compiler_install_compiler_options (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spvc_compiler_options_set_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spvc_context_create (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  spvc_context_create_compiler (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  spvc_context_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spvc_context_parse_spirv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  spvc_context_set_error_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* spvc_get_commit_revision_and_timestamp () ; 
 int /*<<< orphan*/  spvc_get_version (unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  stderr ; 
 unsigned int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
	const char *rev = NULL;

	spvc_context context = NULL;
	spvc_parsed_ir ir = NULL;
	spvc_compiler compiler_glsl = NULL;
	spvc_compiler compiler_hlsl = NULL;
	spvc_compiler compiler_msl = NULL;
	spvc_compiler compiler_cpp = NULL;
	spvc_compiler compiler_json = NULL;
	spvc_compiler compiler_none = NULL;
	spvc_compiler_options options = NULL;
	spvc_resources resources = NULL;
	SpvId *buffer = NULL;
	size_t word_count = 0;

	rev = spvc_get_commit_revision_and_timestamp();
	if (!rev || *rev == '\0')
		return 1;

	printf("Revision: %s\n", rev);

	if (argc != 5)
		return 1;

	if (read_file(argv[1], &buffer, &word_count) < 0)
		return 1;

	unsigned abi_major, abi_minor, abi_patch;
	spvc_get_version(&abi_major, &abi_minor, &abi_patch);
	if (abi_major != strtoul(argv[2], NULL, 0))
	{
		fprintf(stderr, "VERSION_MAJOR mismatch!\n");
		return 1;
	}

	if (abi_minor != strtoul(argv[3], NULL, 0))
	{
		fprintf(stderr, "VERSION_MINOR mismatch!\n");
		return 1;
	}

	if (abi_patch != strtoul(argv[4], NULL, 0))
	{
		fprintf(stderr, "VERSION_PATCH mismatch!\n");
		return 1;
	}

	SPVC_CHECKED_CALL(spvc_context_create(&context));
	spvc_context_set_error_callback(context, error_callback, NULL);
	SPVC_CHECKED_CALL(spvc_context_parse_spirv(context, buffer, word_count, &ir));
	SPVC_CHECKED_CALL(spvc_context_create_compiler(context, SPVC_BACKEND_GLSL, ir, SPVC_CAPTURE_MODE_COPY, &compiler_glsl));
	SPVC_CHECKED_CALL(spvc_context_create_compiler(context, SPVC_BACKEND_HLSL, ir, SPVC_CAPTURE_MODE_COPY, &compiler_hlsl));
	SPVC_CHECKED_CALL(spvc_context_create_compiler(context, SPVC_BACKEND_MSL, ir, SPVC_CAPTURE_MODE_COPY, &compiler_msl));
	SPVC_CHECKED_CALL(spvc_context_create_compiler(context, SPVC_BACKEND_CPP, ir, SPVC_CAPTURE_MODE_COPY, &compiler_cpp));
	SPVC_CHECKED_CALL(spvc_context_create_compiler(context, SPVC_BACKEND_JSON, ir, SPVC_CAPTURE_MODE_COPY, &compiler_json));
	SPVC_CHECKED_CALL(spvc_context_create_compiler(context, SPVC_BACKEND_NONE, ir, SPVC_CAPTURE_MODE_TAKE_OWNERSHIP, &compiler_none));

	SPVC_CHECKED_CALL(spvc_compiler_create_compiler_options(compiler_none, &options));
	SPVC_CHECKED_CALL(spvc_compiler_install_compiler_options(compiler_none, options));
	SPVC_CHECKED_CALL(spvc_compiler_create_compiler_options(compiler_json, &options));
	SPVC_CHECKED_CALL(spvc_compiler_install_compiler_options(compiler_json, options));
	SPVC_CHECKED_CALL(spvc_compiler_create_compiler_options(compiler_cpp, &options));
	SPVC_CHECKED_CALL(spvc_compiler_install_compiler_options(compiler_cpp, options));
	SPVC_CHECKED_CALL(spvc_compiler_create_compiler_options(compiler_msl, &options));
	SPVC_CHECKED_CALL(spvc_compiler_install_compiler_options(compiler_msl, options));
	SPVC_CHECKED_CALL(spvc_compiler_create_compiler_options(compiler_hlsl, &options));
	SPVC_CHECKED_CALL(spvc_compiler_options_set_uint(options, SPVC_COMPILER_OPTION_HLSL_SHADER_MODEL, 50));
	SPVC_CHECKED_CALL_NEGATIVE(spvc_compiler_options_set_uint(options, SPVC_COMPILER_OPTION_MSL_PLATFORM, 1));
	SPVC_CHECKED_CALL(spvc_compiler_install_compiler_options(compiler_hlsl, options));
	SPVC_CHECKED_CALL(spvc_compiler_create_compiler_options(compiler_glsl, &options));
	SPVC_CHECKED_CALL(spvc_compiler_install_compiler_options(compiler_glsl, options));

	SPVC_CHECKED_CALL(spvc_compiler_create_shader_resources(compiler_none, &resources));
	dump_resources(compiler_none, resources);
	compile(compiler_glsl, "GLSL");
	compile(compiler_hlsl, "HLSL");
	compile(compiler_msl, "MSL");
	compile(compiler_json, "JSON");
	compile(compiler_cpp, "CPP");

	spvc_context_destroy(context);
	free(buffer);
	return 0;
}