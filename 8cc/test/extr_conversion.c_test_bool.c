__attribute__((used)) static void test_bool() {
    _Bool v = 3;
    expect(1, v);
    v = 5;
    expect(1, v);
    v = 0.5;
    expect(1, v);
    v = 0.0;
    expect(0, v);
}