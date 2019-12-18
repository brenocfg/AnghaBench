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
struct TYPE_4__ {int /*<<< orphan*/  blend_mode_add; int /*<<< orphan*/  blend_mode_normal; } ;
struct TYPE_3__ {int /*<<< orphan*/  hostMem; } ;

/* Variables and functions */
 unsigned int DISPLAY_BUFFER_COUNT ; 
 int DISPLAY_HEIGHT ; 
 int DISPLAY_STRIDE_IN_PIXELS ; 
 int /*<<< orphan*/  VITA2D_DEBUG (char*) ; 
 int /*<<< orphan*/  _vita2d_colorVertexProgram ; 
 int /*<<< orphan*/  _vita2d_context ; 
 TYPE_2__ _vita2d_fragmentPrograms ; 
 int /*<<< orphan*/  _vita2d_free_fragment_programs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _vita2d_textureVertexProgram ; 
 int /*<<< orphan*/  clearFragmentProgram ; 
 int /*<<< orphan*/  clearFragmentProgramId ; 
 int /*<<< orphan*/  clearVertexProgram ; 
 int /*<<< orphan*/  clearVertexProgramId ; 
 int /*<<< orphan*/  clearVerticesUid ; 
 int /*<<< orphan*/  colorFragmentProgramId ; 
 int /*<<< orphan*/  colorVertexProgramId ; 
 TYPE_1__ contextParams ; 
 int /*<<< orphan*/  depthBufferUid ; 
 int /*<<< orphan*/ * displayBufferData ; 
 int /*<<< orphan*/ * displayBufferSync ; 
 int /*<<< orphan*/ * displayBufferUid ; 
 int /*<<< orphan*/  fragmentRingBufferUid ; 
 int /*<<< orphan*/  fragmentUsseRingBufferUid ; 
 int /*<<< orphan*/  fragment_usse_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpu_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  linearIndicesUid ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  patcherBufferUid ; 
 int /*<<< orphan*/  patcherFragmentUsseUid ; 
 int /*<<< orphan*/  patcherVertexUsseUid ; 
 int /*<<< orphan*/  poolUid ; 
 int /*<<< orphan*/  renderTarget ; 
 int /*<<< orphan*/  sceGxmDestroyContext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGxmDestroyRenderTarget (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGxmDisplayQueueFinish () ; 
 int /*<<< orphan*/  sceGxmFinish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGxmShaderPatcherDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGxmShaderPatcherReleaseFragmentProgram (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGxmShaderPatcherReleaseVertexProgram (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGxmShaderPatcherUnregisterProgram (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGxmSyncObjectDestroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sceGxmTerminate () ; 
 int /*<<< orphan*/  shaderPatcher ; 
 int /*<<< orphan*/  stencilBufferUid ; 
 int /*<<< orphan*/  textureFragmentProgramId ; 
 int /*<<< orphan*/  textureTintFragmentProgramId ; 
 int /*<<< orphan*/  textureVertexProgramId ; 
 int /*<<< orphan*/  vdmRingBufferUid ; 
 int /*<<< orphan*/  vertexRingBufferUid ; 
 int /*<<< orphan*/  vertex_usse_free (int /*<<< orphan*/ ) ; 
 scalar_t__ vita2d_initialized ; 

int vita2d_fini()
{
	unsigned int i;

	if (!vita2d_initialized) {
		VITA2D_DEBUG("libvita2d is not initialized!\n");
		return 1;
	}

	// wait until rendering is done
	sceGxmFinish(_vita2d_context);

	// clean up allocations
	sceGxmShaderPatcherReleaseFragmentProgram(shaderPatcher, clearFragmentProgram);
	sceGxmShaderPatcherReleaseVertexProgram(shaderPatcher, clearVertexProgram);
	sceGxmShaderPatcherReleaseVertexProgram(shaderPatcher, _vita2d_colorVertexProgram);
	sceGxmShaderPatcherReleaseVertexProgram(shaderPatcher, _vita2d_textureVertexProgram);

	_vita2d_free_fragment_programs(&_vita2d_fragmentPrograms.blend_mode_normal);
	_vita2d_free_fragment_programs(&_vita2d_fragmentPrograms.blend_mode_add);

	gpu_free(linearIndicesUid);
	gpu_free(clearVerticesUid);

	// wait until display queue is finished before deallocating display buffers
	sceGxmDisplayQueueFinish();

	// clean up display queue
	gpu_free(depthBufferUid);
	for (i = 0; i < DISPLAY_BUFFER_COUNT; i++) {
		// clear the buffer then deallocate
		memset(displayBufferData[i], 0, DISPLAY_HEIGHT*DISPLAY_STRIDE_IN_PIXELS*4);
		gpu_free(displayBufferUid[i]);

		// destroy the sync object
		sceGxmSyncObjectDestroy(displayBufferSync[i]);
	}

	// free the depth and stencil buffer
	gpu_free(depthBufferUid);
	gpu_free(stencilBufferUid);

	// unregister programs and destroy shader patcher
	sceGxmShaderPatcherUnregisterProgram(shaderPatcher, clearFragmentProgramId);
	sceGxmShaderPatcherUnregisterProgram(shaderPatcher, clearVertexProgramId);
	sceGxmShaderPatcherUnregisterProgram(shaderPatcher, colorFragmentProgramId);
	sceGxmShaderPatcherUnregisterProgram(shaderPatcher, colorVertexProgramId);
	sceGxmShaderPatcherUnregisterProgram(shaderPatcher, textureFragmentProgramId);
	sceGxmShaderPatcherUnregisterProgram(shaderPatcher, textureTintFragmentProgramId);
	sceGxmShaderPatcherUnregisterProgram(shaderPatcher, textureVertexProgramId);

	sceGxmShaderPatcherDestroy(shaderPatcher);
	fragment_usse_free(patcherFragmentUsseUid);
	vertex_usse_free(patcherVertexUsseUid);
	gpu_free(patcherBufferUid);

	// destroy the render target
	sceGxmDestroyRenderTarget(renderTarget);

	// destroy the _vita2d_context
	sceGxmDestroyContext(_vita2d_context);
	fragment_usse_free(fragmentUsseRingBufferUid);
	gpu_free(fragmentRingBufferUid);
	gpu_free(vertexRingBufferUid);
	gpu_free(vdmRingBufferUid);
	free(contextParams.hostMem);

	gpu_free(poolUid);

	// terminate libgxm
	sceGxmTerminate();

	/* if (pgf_module_was_loaded != SCE_SYSMODULE_LOADED)
		sceSysmoduleUnloadModule(SCE_SYSMODULE_PGF); */

	vita2d_initialized = 0;

	return 1;
}