__attribute__((used)) static void s68k_unused_16_w(unsigned int address, unsigned int data)
{
#ifdef LOGERROR
  error("[SUB 68k] Unused write16 %08X = %04X (%08X)\n", address, data, s68k.pc);
#endif
}